#include "./json.h"

using namespace std;

JSONDataSource::JSONDataSource(const std::string &path) : FileDataSource(path), reachedEndOfArray(false) {
  // get first character
  char c = file.get();
  if (c != '[') {
    throw std::runtime_error("JSON array file must start with [");
  }
  auto block = readBlock();
  if (block.first.empty()) {
    throw std::runtime_error("JSON array file must contain at least one object");
  }
  header = block.first;
  nextRow = block.second;
}

bool JSONDataSource::hasNextRow() const {
  // TODO
  return reachedEndOfArray;
}

const std::vector<std::string> JSONDataSource::getNextRow() {
  return std::vector<std::string>();
}

void JSONDataSource::reset() {
  FileDataSource::reset();
}

std::pair<std::vector<std::string>, std::vector<std::string> > JSONDataSource::readBlock() {
  // find first {
  char c;
  while ((c = file.get()) != '{') {
    if (c == EOF) {
      throw std::runtime_error("Unexpected end of file");
    }
  }
  // We know that objects are not nested, so just look for next }
  std::string unparsedJsonObject;
  while ((c = file.get()) != '}') {
    if (c == EOF) {
      throw std::runtime_error("Unexpected end of file");
    }
    unparsedJsonObject += c;
  }
  return parseBlockString(unparsedJsonObject);
}

std::pair<std::vector<std::string>, std::vector<std::string> >
JSONDataSource::parseBlockString(const std::string &unparsedJsonObject) {
  vector<string> header;
  vector<string> row;
  bool inQuotes = false;
  string currentString;
  for (char c: unparsedJsonObject) {
    if (c == '"') {
      inQuotes = !inQuotes;
    } else if (c == ':' && !inQuotes) {
      if (currentString.empty()) {
        throw std::runtime_error("Invalid JSON object - key missing");
      }
      header.push_back(currentString);
      currentString = "";
    } else if (c == ',' && !inQuotes) {
      if (currentString.empty()) {
        throw std::runtime_error("Invalid JSON object - no value found for key " + header.back());
      }
      row.push_back(currentString);
      currentString = "";
    } else if (c != ' ' && c != '\n' && c != '\t') {
      currentString += c;
    }
  }
  // last value does not have , after it
  row.push_back(currentString);
  if (currentString.empty()) {
    throw std::runtime_error("Invalid JSON object - no value found for last key");
  }
  if (header.size() != row.size()) {
    throw std::runtime_error("Invalid JSON object - header and row have different number of values");
  }
  return make_pair(header, row);
}