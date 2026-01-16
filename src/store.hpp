#pragma once

#include <SQLiteCpp/Database.h>

std::string format_fs_error(const std::filesystem ::filesystem_error &e);
void createPathIfNotExist(std::string p);
SQLite::Database createAndGetDBPath();
