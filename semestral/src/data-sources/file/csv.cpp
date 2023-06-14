#include "csv.h"
#include <iostream>
#include <sstream>
#include "../../utils/utils.h"

using namespace std;

CSVDataSource::CSVDataSource(const string &path, const string &name)
        : FileDataSource(path, name) {
  CSVDataSource::reset();
}

const vector<string> CSVDataSource::getNextRow() {
  vector<string> nextRow = readNextRow();
  if (nextRow.empty()) {
    return nextRow;
  }
  if (nextRow.size() != this->header.size()) {
    throw runtime_error("Could not read row, CSV file has inconsistent number of columns");
  }
  return nextRow;
}

vector<string> CSVDataSource::readNextRow() {
  string line;
  getline(file, line);
  stringstream ss(line);
  string token;
  vector<string> row;
  while (getline(ss, token, ',')) {
    row.push_back(token);
  }
  return row;
}

void CSVDataSource::reset() {
  try {
    FileDataSource::reset();
    this->header = vectorToIndexMap(readNextRow());
  } catch (...) {
    throw runtime_error("Could not read header, CSV file is empty");
  }
}

unique_ptr<AbstractDataSource> CSVDataSource::clone() const {
  return make_unique<CSVDataSource>(this->path, this->name);
}
