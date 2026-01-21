#pragma once

#include <SQLiteCpp/Database.h>

std::string format_fs_error(const std::filesystem ::filesystem_error &e);
void createPathIfNotExist(std::string p);
std::unique_ptr<SQLite::Database> createAndGetDBPath();
void setupDB(SQLite::Database &db);
