#include "formatter.hpp"
#include "store.hpp"
#include <SQLiteCpp/Database.h>
#include <chrono>

void print_current_month() {
  auto now = std::chrono::zoned_time{std::chrono::current_zone(),
                                     std::chrono::system_clock::now()}
                 .get_local_time();
  std::chrono::year_month_day current_date{
      std::chrono::floor<std::chrono::days>(now)};

  unsigned int month = static_cast<unsigned int>(current_date.month());
  int year = static_cast<int>(current_date.year());

  print_month(static_cast<int>(month), year);
}

int main() {
  print_current_month();

  auto store = createAndGetDBPath();
  setupDB(*store);

  return 0;
}
