#include "formatter.hpp"
#include "date.hpp"
#include "store.hpp"
#include <format>
#include <iostream>
#include <termcolor/termcolor.hpp>
#include <vector>

const std::vector<std::string> monthNames = {
    "January", "February", "March",     "April",   "May",      "June",
    "July",    "August",   "September", "October", "November", "December"};

bool is_holiday(std::vector<Holiday> holidays, int today) {
  for (Holiday holiday : holidays) {
    if (holiday.date.day == today) {
      return true;
    }
  }
  return false;
}

void print_month(int month, int year, SQLite::Database &db) {
  Date today = get_today();

  std::string date = monthNames[static_cast<unsigned long>(today.month) - 1] +
                     " " + std::to_string(today.year);

  std::vector<Holiday> holidays = get_month_events(db, today.month, today.year);

  std::cout << std::format("{:^{}}", date, 20) << std::endl;

  std::cout << "M  T  W  T  F  " << termcolor::bright_red << "S  S"
            << termcolor::reset << std::endl;

  int last_month_day_count = get_daycount(month - 1);
  if (month == 1) {
    last_month_day_count = get_daycount(12);
  }

  int starting_weekday = get_weekday(1, month, year);

  int last_month_day = last_month_day_count - starting_weekday + 1;

  // the previous month's dates
  std::cout << termcolor::bright_grey;
  for (int i = 1; i <= starting_weekday; i++) {
    std::cout << last_month_day << " ";
    last_month_day++;
  }
  std::cout << termcolor::reset;

  // this month's dates
  for (int i = 1; i <= get_daycount(month); i++) {
    if (is_holiday(i, month, year)) {
      std::cout << termcolor::bright_red;
    }
    // is it today
    if (today.day == i && month == today.month && year == today.year) {
      std::cout << termcolor::on_blue;
    }
    // is it a holiday
    if (is_holiday(holidays, today.day)) {
      std::cout << termcolor::bright_red;
    }

    std::cout << i;
    std::cout << termcolor::reset;

    if (1 <= i && i <= 9) {
      std::cout << "  ";
    } else {
      std::cout << " ";
    }

    if (get_weekday(i, month, year) == 6) {
      std::cout << std::endl;
    }
  }

  // the next month's dates
  int next_month_start_count =
      7 - get_weekday(get_daycount(month), month, year) - 1;

  int next_month = month + 1;
  // in december we do it for the next year
  if (next_month == 13) {
    next_month = 1;
  }
  std::cout << termcolor::bright_grey;
  for (int i = 1; i <= next_month_start_count; i++) {
    std::cout << i << "  ";
  }
  std::cout << termcolor::reset;
  std::cout << std::endl;
}
