#pragma once

#include "date.hpp"
#include <SQLiteCpp/Database.h>

void print_month(int month, int year, SQLite::Database &db, Date today);
