#include "client.hpp"
#include "date.hpp"
#include "panic.hpp"
#include <SQLiteCpp/Database.h>
#include <chrono>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

std::vector<Holiday> get_events(int year, std::string countryCode) {
  std::string str_year = std::to_string(year);
  std::string endpoint = "https://date.nager.at/api/v3/PublicHolidays/" +
                         str_year + "/" + countryCode;
  cpr::Response r = cpr::Get(cpr::Url{endpoint}, cpr::VerifySsl{false});
  std::string body = r.text;

  std::vector<Holiday> holidays;
  Date day;

  try {
    json parsed_json = json::parse(body);

    for (const auto &item : parsed_json) {
      Holiday holiday;

      std::string date = item["date"].get<std::string>();
      std::chrono::year_month_day ymd;
      std::istringstream ss(date);
      ss >> std::chrono::parse("%F", ymd);

      if (!ss.fail()) {
        day.year = static_cast<int>(ymd.year());
        day.month = static_cast<int>(static_cast<unsigned int>(ymd.month()));
        day.day = static_cast<int>(static_cast<unsigned int>(ymd.day()));

      } else {
        panic("failed to parse date string: " + date);
      }

      holiday.name = item["name"].get<std::string>();
      holiday.date = day;

      holidays.push_back(holiday);
    }

  } catch (json::parse_error &e) {
    std::string what(e.what());
    panic("json parsing error: " + what);
  } catch (json::type_error &e) {
    std::string what(e.what());
    panic("jsontype error: " + what);
  }

  return holidays;
}
