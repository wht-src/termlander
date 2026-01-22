#pragma once

#include "date.hpp"
#include <SQLiteCpp/Database.h>
#include <vector>

std::string format_fs_error(const std::filesystem ::filesystem_error &e);
void create_path_if_not_exist(std::string p);
std::unique_ptr<SQLite::Database> create_and_get_db_path();
void setup_db(SQLite::Database &db);
bool check_year_exist(SQLite::Database &db, int year);
void store_event(SQLite::Database &db, int year, std::string ccode);
void update_event_db(SQLite::Database &db);
std::vector<Holiday> get_month_events(SQLite::Database &db, int month,
                                      int year);
