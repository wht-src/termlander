#include "date.hpp"
#include "formatter.hpp"
#include "store.hpp"
#include <SQLiteCpp/Database.h>

void print_current_month() {
  Date today = get_today();
  print_month(today.month, today.year);
}

int main() {
  print_current_month();

  auto store = createAndGetDBPath();
  setupDB(*store);

  return 0;
}
