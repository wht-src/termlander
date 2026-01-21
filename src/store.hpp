#pragma once

#include <SQLiteCpp/Database.h>

std::string format_fs_error(const std::filesystem ::filesystem_error &e);
void createPathIfNotExist(std::string p);
std::unique_ptr<SQLite::Database> createAndGetDBPath();
void setupDB(SQLite::Database &db);
bool checkYearExist(SQLite::Database &db, int year);
void storeEvent(SQLite::Database &db, int year, std::string ccode);
void update_event_db(SQLite::Database &db);
