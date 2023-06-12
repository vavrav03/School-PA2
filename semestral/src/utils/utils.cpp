#include "./utils.h"

std::string toLowerCase(const std::string &stringToConvert) {
  std::string result = stringToConvert;
  for (char &c: result) {
    c = tolower(c);
  }
  return result;
}