#include "csv.h"
#include "../../data-types/string/string-type.h"
#include <iostream>
#include <sstream>

using namespace std;

CSVDataSource::CSVDataSource(const string &path)
    : AbstractDataSource(), file(path) {
  if (!file.is_open()) {
    throw runtime_error("Could not open file");
  }
  try {
    this->header = readUnparsedRow();
  } catch (...) {
    throw runtime_error("Could not read header, CSV file is empty");
  }
}

bool CSVDataSource::hasNextRow() const { return !file.eof(); }

const DataRow CSVDataSource::getNextRow() {
  vector<string> unparsedRow = readUnparsedRow();
  DataRow nextRow;
  for (string &value : unparsedRow) {
    nextRow.addField(new StringType(value));
  }
  return nextRow;
}

const vector<string> CSVDataSource::readUnparsedRow() {
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

CSVDataSource::~CSVDataSource() { file.close(); }