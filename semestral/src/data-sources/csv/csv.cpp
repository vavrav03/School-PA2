#include "./csv.h"
#include "../../data-row/data-row.h"
#include <iostream>
#include <sstream>

using namespace std;

CSVDataSource::CSVDataSource(const string &path)
    : AbstractDataSource(), file(path) {
  if(file.fail()) {
    throw runtime_error("Could not open file");
  }
  try {
    readUnparsedRow();
    this->header = this->nextRow;
    readUnparsedRow();
  } catch (...) {
    throw runtime_error("Could not read header, CSV file is empty");
  }
}

bool CSVDataSource::hasNextRow() const { return nextRow.size() > 0; }

const DataRow CSVDataSource::getNextRow() {
  if(this->nextRow.size() == 0) {
    throw runtime_error("Could not read row, CSV file is empty");
  }
  if(this->nextRow.size() != this->header.size()) {
    throw runtime_error("Could not read row, CSV file has inconsistent number of columns");
  }
  DataRow nextRow;
  for (string &value : this->nextRow) {
    nextRow.addField(value);
  }
  readUnparsedRow();
  return nextRow;
}

void CSVDataSource::readUnparsedRow() {
  string line;
  getline(file, line);
  stringstream ss(line);
  string token;
  vector<string> row;
  while (getline(ss, token, ',')) {
    row.push_back(token);
  }
  this->nextRow = row;
}

CSVDataSource::~CSVDataSource() { file.close(); }