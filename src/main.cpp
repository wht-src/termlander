#include "date.hpp"
#include "formatter.hpp"
#include "store.hpp"
#include <SQLiteCpp/Database.h>

void print_month(SQLite::Database &db) {
  Date today = get_today();
  print_month(today.month, today.year, db);
}

int main() {
  auto store = createAndGetDBPath();
  setupDB(*store);
  update_event_db(*store);

  print_month(*store);

  return 0;
}
