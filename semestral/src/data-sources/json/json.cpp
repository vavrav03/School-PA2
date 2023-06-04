#include "./json.h"

JSONDataSource::JSONDataSource(const std::string &path): FileDataSource(path) {}

bool JSONDataSource::hasNextRow() const {
  return false;
}

const std::vector<std::string> JSONDataSource::getNextRow() {
  return std::vector<std::string>();
}

void JSONDataSource::reset() {
  FileDataSource::reset();
}
