#include "locale.hpp"

#ifdef _WIN32
#include <windows.h>
#endif

std::string get_country_code() {
#if defined(__linux__) || defined(__APPLE__) || defined(__unix__)
  std::setlocale(LC_ALL, "");
  char *loc = std::setlocale(LC_ALL, NULL);

  if (loc) {
    std::string localeStr(loc);
    size_t underscore = localeStr.find('_');
    if (underscore != std::string::npos) {
      return localeStr.substr(underscore + 1, 2);
    }
  }
  return "";
#else
  // untested~
  wchar_t locale_name[LOCALE_NAME_MAX_LENGTH];
  if (GetUserDefaultLocaleName(locale_name, LOCALE_NAME_MAX_LENGTH) > 0) {
    std::wstring wstr_locale(locale_name);
    size_t hyphen_pos = wstr_locale.find(L'-');
    if (hyphen_pos != std::wstring::npos &&
        hyphen_pos + 1 < wstr_locale.length()) {
      std::wstring wstr_country_code = wstr_locale.substr(hyphen_pos + 1);
      int len = WideCharToMultiByte(CP_UTF8, 0, wstr_country_code.c_str(), -1,
                                    NULL, 0, NULL, NULL);
      std::string country_code(len, '\0');
      WideCharToMultiByte(CP_UTF8, 0, wstr_country_code.c_str(), -1,
                          &country_code[0], len, NULL, NULL);
      return country_code;
    }
  }
  return "";
#endif
}
