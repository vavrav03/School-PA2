#include "./utils.h"

using namespace std;

string toLowerCase(const string &stringToConvert) {
  string result = stringToConvert;
  for (char &c : result) {
    c = tolower(c);
  }
  return result;
}

string getNameFromPath(string const &path) {
#ifdef _WIN32
  const char delimiter = '\\';
#else
  const char delimiter = '/';
#endif
  return path.substr(path.find_last_of(delimiter) + 1);
}

string getNameWithoutExtension(string const &fileName) {
  string name = getNameFromPath(fileName);
  size_t const pos(name.find_first_of('.'));
  if (pos == string::npos) {
    return name;
  }
  return name.substr(0, pos);
}

string getExtensionFromPath(string const &fileName) {
  string name = getNameFromPath(fileName);
  size_t const pos(name.find_first_of('.'));
  if (pos == string::npos) {
    return "";
  }
  return name.substr(pos + 1);
}

