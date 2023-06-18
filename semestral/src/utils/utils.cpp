#include "./utils.h"

using namespace std;

string toLowerCase(const string &stringToConvert) {
  string result = stringToConvert;
  for (char &c : result) {
    c = tolower(c);
  }
  return result;
}

string getNameFromPath(const string &path) {
#ifdef _WIN32
  const char delimiter = '\\';
#else
  const char delimiter = '/';
#endif
  return path.substr(path.find_last_of(delimiter) + 1);
}

string getNameWithoutExtension(const string &fileName) {
  string name = getNameFromPath(fileName);
  size_t const pos(name.find_first_of('.'));
  if (pos == string::npos) {
    return name;
  }
  return name.substr(0, pos);
}

string getExtensionFromPath(const string &fileName) {
  string name = getNameFromPath(fileName);
  size_t const pos(name.find_first_of('.'));
  if (pos == string::npos) {
    return "";
  }
  return name.substr(pos + 1);
}

string getRandomString(size_t length) {
  static const char alphanum[] =
      "0123456789abcdefghijklmnopqrstuvwxyz";

  string result(length, ' ');
  result[0] = alphanum[rand() % (sizeof(alphanum) - 10) + 10];
  for (size_t i = 1; i < length; ++i) {
    result[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
  }
  return result;
}

