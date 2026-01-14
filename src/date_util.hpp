#pragma once

enum class Ctype { Gregorian, Julian };

bool is_leap_year(int year);
int get_daycount(int month);
int get_weekday(int day, int month, int year, Ctype type = Ctype::Julian);
