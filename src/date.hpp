#pragma once

#include <string>
#include <vector>

enum class Ctype { Gregorian, Julian };

struct Date {
  int year;
  int month;
  int day;
};

struct Holiday {
  Date date;
  std::string name;
};

bool is_leap_year(int year);
int get_daycount(int month);
int get_weekday(int day, int month, int year, Ctype type = Ctype::Julian);
bool is_weekend(int day, int month, int year);
bool is_holiday(int day, std::vector<Holiday> holidays);
void print_if_holiday(int day, std::vector<Holiday> holidays);
Date get_today();
std::string format_date(Date d);
