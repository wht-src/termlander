#include "date.hpp"
#include "formatter.hpp"
#include "store.hpp"
#include <SQLiteCpp/Database.h>

void print_cal(SQLite::Database &db, int month, int day_override) {
  Date today = get_today();
  if (month != 0) {
    today.month = month;
    today.day = 0;
  }
  if (day_override != 0) {
    today.day = day_override;
  }
  print_month(today.month, today.year, db, today);
}

int main(int argc, char *argv[]) {
  auto store = createAndGetDBPath();
  setupDB(*store);
  update_event_db(*store);

  if (argc == 1) {
    print_cal(*store, 0, 0);
  } else {
    int desired_month = std::stoi(argv[1]);
    print_cal(*store, desired_month, 0);
  }

  return 0;
}
