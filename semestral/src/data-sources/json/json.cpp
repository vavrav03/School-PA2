#include "./json.h"

JSONDataSource::JSONDataSource(const std::string &path) {}

bool JSONDataSource::hasNextRow() const {
  return false;
}

const std::vector<std::string> JSONDataSource::getNextRow() {
  return std::vector<std::string>();
}
