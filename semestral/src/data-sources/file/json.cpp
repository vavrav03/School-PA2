#include "json.h"
#include "../../utils/utils.h"

using namespace std;

JSONDataSource::JSONDataSource(const std::string &path, const std::string &name) : FileDataSource(path, name),
                                                                                   reachedEndOfArray(false) {
  readFirstBlockAndSetHeader();
}

const std::vector<std::string> JSONDataSource::getNextRow() {
  if (reachedEndOfArray) {
    return vector<string>();
  }
  vector<string> result = nextRow;
  auto block = readBlock();
  if (block.first.empty()) {
    reachedEndOfArray = true;
    return result;
  }
  if (block.first.size() != header.size()) {
    throw std::runtime_error("JSON array file must contain objects with the same number of fields");
  }
  vector<string> newRowInBuilding(this->header.size());
  vector<int> setCounts(this->header.size(), 0);
  for (size_t i = 0; i < block.first.size(); i++) {
    newRowInBuilding[header[block.first[i]]] = block.second[i];
    setCounts[header[block.first[i]]]++;
  }
  for (size_t i = 0; i < this->header.size(); i++) {
    if (setCounts[i] != 1) {
      throw std::runtime_error("JSON array file must contain objects with the same fields");
    }
  }
  nextRow = newRowInBuilding;
  return result;
}

void JSONDataSource::reset() {
  FileDataSource::reset();
  reachedEndOfArray = false;
  header = unordered_map<string, size_t>();
  nextRow = vector<string>();
  readFirstBlockAndSetHeader();
}

void JSONDataSource::readFirstBlockAndSetHeader() {
  // get first character
  char c = file.get();
  if (c != '[') {
    throw std::runtime_error("JSON array file must start with [");
  }
  auto block = readBlock();
  if (block.first.empty()) {
    throw std::runtime_error("JSON array file must contain at least one object");
  }
  header = vectorToIndexMap(block.first);
  nextRow = block.second;
}

std::pair<std::vector<std::string>, std::vector<std::string> > JSONDataSource::readBlock() {
  // find first {
  char c;
  int commaCounter = 0;
  while ((c = file.get()) != '{') {
    if (c == EOF) {
      throw std::runtime_error("Unexpected end of file");
    } else if (c == ']') {
      return make_pair(vector<string>(), vector<string>());
    } else if (c == ',') {
      commaCounter++;
    } else if (c != ' ' && c != '\n' && c != '\r' && c != '\t') {
      throw std::runtime_error("Unexpected character " + string(1, c) + " found in JSON array file");
    }
  }
  if (commaCounter != 1 && !header.empty()) {
    throw std::runtime_error("JSON is in invalid format - there must be exactly one comma between objects");
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
  for (char c : unparsedJsonObject) {
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