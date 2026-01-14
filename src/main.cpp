#include "formatter.hpp"
#include <iostream>

int main() {
  int month, year;
  std::cout << "Year: ";
  std::cin >> year;
  std::cout << "Month: ";
  std::cin >> month;

  print_month(month, year);

  return 0;
}
