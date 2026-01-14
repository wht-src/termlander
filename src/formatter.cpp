#include "formatter.hpp"
#include "date_util.hpp"
#include <iostream>
#include <termcolor/termcolor.hpp>

void print_month(int month, int year) {
  std::cout << "M  T  W  T  F  " << termcolor::red << "S  S" << termcolor::reset
            << std::endl;

  int last_month_day_count = get_daycount(month - 1);
  if (month == 1) {
    last_month_day_count = get_daycount(12);
  }

  int starting_weekday = get_weekday(1, month, year);

  int last_month_day = last_month_day_count - starting_weekday + 1;

  for (int i = 1; i <= starting_weekday; i++) {
    std::cout << last_month_day << " ";
    last_month_day++;
  }

  for (int i = 1; i <= get_daycount(month); i++) {
    if (is_holiday(i, month, year)) {
      std::cout << termcolor::red;
    }

    if (1 <= i && i <= 9) {
      std::cout << i << "  ";
    } else {
      std::cout << i << " ";
    }

    if (get_weekday(i, month, year) == 6) {
      std::cout << std::endl;
    }
    std::cout << termcolor::reset;
  }

  int next_month_start_count =
      7 - get_weekday(get_daycount(month), month, year) - 1;

  int next_month = month + 1;
  int target_year = year;
  if (next_month == 13) {
    next_month = 1;
    target_year++;
  }
  for (int i = 1; i <= next_month_start_count; i++) {
    if (is_holiday(i, next_month, target_year)) {
      std::cout << termcolor::red;
    }
    std::cout << i << "  ";
    std::cout << termcolor::reset;
  }
}
