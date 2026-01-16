#include "store.hpp"

#include "panic.hpp"
#include <SQLiteCpp/Database.h>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

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
SQLite::Database createAndGetDBPath() {
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

  try {
    SQLite::Database db(dbPath + "store.db3",
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    return db;

  } catch (std::exception &e) {
    std::string errmsg = e.what();
    panic("SQLite exception: " + errmsg);
    exit(-1);
  }
}
