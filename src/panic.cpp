#include "panic.hpp"
#include <cstdlib>
#include <iostream>
#include <termcolor/termcolor.hpp>

void panic(std::string msg, int code) {
  std::cerr << termcolor::bright_red;
  std::cerr << msg << std::endl;
  std::cerr << termcolor::reset;
  exit(code);
}
