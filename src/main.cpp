#include "formatter.hpp"
#include <chrono>

int main() {
  auto now = std::chrono::zoned_time{std::chrono::current_zone(),
                                     std::chrono::system_clock::now()}
                 .get_local_time();
  std::chrono::year_month_day current_date{
      std::chrono::floor<std::chrono::days>(now)};

  unsigned int month = static_cast<unsigned int>(current_date.month());
  int year = static_cast<int>(current_date.year());

  print_month(static_cast<int>(month), year);

  return 0;
}
