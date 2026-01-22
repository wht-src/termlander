#include "store.hpp"

#include "client.hpp"
#include "date.hpp"
#include "locale.hpp"
#include "panic.hpp"
#include <SQLiteCpp/Database.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

std::string format_fs_error(const std::filesystem::filesystem_error &e) {
  std::string msg;

  msg += e.what();

  const std::error_code &ec = e.code();
  msg += " (error_code: ";
  msg += std::to_string(ec.value());
  msg += ", category: ";
  msg += ec.category().name();
  msg += ")";

  if (!e.path1().empty()) {
    msg += " [path1: ";
    msg += e.path1().string();
    msg += "]";
  }

  if (!e.path2().empty()) {
    msg += " [path2: ";
    msg += e.path2().string();
    msg += "]";
  }

  return msg;
}

void createPathIfNotExist(std::string p) {
  namespace fs = std::filesystem;

  try {
    fs::create_directories(p);

    // Optionally, validate it's a directory
    if (!fs::exists(p)) {
      panic(p + " was not created and does not exist");
    }
    if (!fs::is_directory(p)) {
      panic(p + " exists but not a directory");
    }

    // at this point the file is created and we just return
    return;
  } catch (const std::filesystem::filesystem_error &e) {
    panic(format_fs_error(e));
  }
}

// creates database if not exist
std::unique_ptr<SQLite::Database> createAndGetDBPath() {
  std::string dbPath;

#ifdef _WIN32
  const char *appData = getenv("APPDATA");
  if (appData) {
    configPath = std::string(appData) + "\\termlander\\";
  } else {
    panic("failed to getenv(\"APPDATA\")");
  }
#else // unix
  const char *homeDir = getenv("HOME");
  if (homeDir) {
    dbPath = std::string(homeDir) + "/.config/termlander/";
  } else {
    panic("failed to getenv(\"HOME\")");
  }
#endif

  createPathIfNotExist(dbPath);

  dbPath += "store.db3";

  try {
    // something tells me this will bite me in the back sooner or later
    auto db = std::make_unique<SQLite::Database>(
        dbPath, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    return db;
  } catch (const std::exception &e) {
    panic(std::string("sqlite exception: ") + e.what());
    std::exit(-1);
  }
}

void setupDB(SQLite::Database &db) {
  const char *cmd = "CREATE TABLE IF NOT EXISTS events ("
                    "eid INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "date DATE NOT NULL,"
                    "name TEXT NOT NULL"
                    ");";
  db.exec(cmd);
}

bool checkYearExist(SQLite::Database &db, int year) {
  try {
    SQLite::Statement query(db,
                            "SELECT 1 FROM events WHERE CAST(strftime('%Y', "
                            "date) AS integer) = ? LIMIT 1;");
    query.bind(1, year);

    if (query.executeStep()) {
      return true;
    } else {
      return false;
    }
  } catch (std::exception &e) {
    std::string what(e.what());
    panic("sqlite exception: " + what);
    return false;
  }
}

void storeEvent(SQLite::Database &db, int year, std::string ccode) {
  for (Holiday &h : get_events(year, ccode)) {
    try {
      SQLite::Statement query(db,
                              "INSERT INTO events (date, name) VALUES (?, ?);");
      query.bind(1, format_date(h.date));
      query.bind(2, h.name);
      query.exec();

    } catch (std::exception &e) {
      std::string what(e.what());
      panic("sqlite exception: " + what);
    }
  }
}

void update_event_db(SQLite::Database &db) {
  Date day = get_today();
  // will not update
  if (checkYearExist(db, day.year)) {
    return;
  }
  std::string ccode = get_country_code();

  if (ccode == "") {
    return;
  }
  storeEvent(db, day.year, ccode);
}

std::vector<Holiday> get_month_events(SQLite::Database &db, int month,
                                      int year) {
  char startDate[11]; // yyyy-mm-dd + null terminator
  char endDate[11];

  snprintf(startDate, sizeof(startDate), "%04d-%02d-01", year, month);
  int nextMonth = month == 12 ? 1 : month + 1;
  int nextYear = month == 12 ? year + 1 : year;
  snprintf(endDate, sizeof(endDate), "%04d-%02d-01", nextYear, nextMonth);

  const char *sql = "SELECT name, STRFTIME('%d', date) FROM events "
                    "WHERE date >= ? AND date < ?";

  try {
    SQLite::Statement query(db, sql);
    query.bind(1, std::string(startDate));
    query.bind(2, std::string(endDate));

    std::vector<Holiday> holidays;
    while (query.executeStep()) {
      Holiday h;
      h.name = query.getColumn(0).getString();
      h.date.day = query.getColumn(1).getInt();
      h.date.month = month;
      h.date.year = year;
      holidays.push_back(h);
    }
    return holidays;

  } catch (const std::exception &e) {
    std::string what(e.what());
    panic("sqlite exception: " + what);
    return {};
  }
}
