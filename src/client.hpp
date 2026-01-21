#pragma once

#include "date.hpp"
#include <SQLiteCpp/Database.h>
#include <string>
#include <vector>

struct Holiday {
  Date date;
  std::string name;
};

std::vector<Holiday> get_events(int year, std::string countryCode);
