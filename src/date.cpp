#include "date.hpp"

bool is_leap_year(int year) { return year % 4 == 0; }

int get_daycount(int month) {
  switch (month) {
  case 2:
    if (is_leap_year(month)) {
      return 29;
    } else {
      return 28;
    }

    // clang-format off
  case 1: case 3: case 5: case 7: case 8: case 10: case 12:
    return 31;
    // clang-format on

  default:
    return 30;
  }
}

int get_weekday(int day, int month, int year, Ctype type) {
  int m = month;
  int y = year;

  if (m == 1) {
    m = 13;
    y--;
  }
  if (m == 2) {
    m = 14;
    y--;
  }

  const int year_of_century = y % 100;
  const int century = y / 100;

  int h;

  const int term1 = day;
  const int term2 = (13 * (m + 1)) / 5;
  const int term3 = year_of_century;
  const int term4 = year_of_century / 4;

  switch (type) {
  case Ctype::Gregorian: {
    const int term5 = century / 4;
    const int term6 = 5 * century;
    h = term1 + term2 + term3 + term4 + term5 + term6;
    break;
  }
  case Ctype::Julian: {
    const int term5_julian = 5;
    h = term1 + term2 + term3 + term4 + term5_julian;
    break;
  }
  default:
    return -1;
  }

  return (h % 7 + 7) % 7;
}

bool is_holiday(int day, int month, int year) {
  // weekend
  if (get_weekday(day, month, year) == 6 ||
      get_weekday(day, month, year) == 5) {
    return true;
  }
  return false;
}
