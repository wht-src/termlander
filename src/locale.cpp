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
  wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
  if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH) > 0) {
    std::wstring wstrLocale(localeName);
    size_t hyphenPos = wstrLocale.find(L'-');
    if (hyphenPos != std::wstring::npos &&
        hyphenPos + 1 < wstrLocale.length()) {
      std::wstring wstrCountryCode = wstrLocale.substr(hyphenPos + 1);
      int len = WideCharToMultiByte(CP_UTF8, 0, wstrCountryCode.c_str(), -1,
                                    NULL, 0, NULL, NULL);
      std::string countryCode(len, '\0');
      WideCharToMultiByte(CP_UTF8, 0, wstrCountryCode.c_str(), -1,
                          &countryCode[0], len, NULL, NULL);
      return countryCode;
    }
  }
  return "";
#endif
}
