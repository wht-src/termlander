#pragma once

#include "date.hpp"
#include <SQLiteCpp/Database.h>
#include <string>
#include <vector>

std::vector<Holiday> get_events(int year, std::string countryCode);
