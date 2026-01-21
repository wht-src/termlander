#pragma once

enum class Ctype { Gregorian, Julian };

struct Date {
  int year;
  int month;
  int day;
};

bool is_leap_year(int year);
int get_daycount(int month);
int get_weekday(int day, int month, int year, Ctype type = Ctype::Julian);
bool is_holiday(int day, int month, int year);
Date get_today();
