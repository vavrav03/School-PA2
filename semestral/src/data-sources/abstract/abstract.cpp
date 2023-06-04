#include "abstract.h"

using namespace std;

AbstractDataSource::AbstractDataSource() = default;

const vector<string> &AbstractDataSource::getHeader() const {
  return this->header;
}

const int AbstractDataSource::getHeaderSize() const {
  return this->header.size();
}

AbstractDataSource::~AbstractDataSource() = default;

FileDataSource::FileDataSource(const std::string &path) : file(path) {
  if (file.fail()) {
    throw runtime_error("File not found");
  }
}

void FileDataSource::reset() {
  file.clear();
  file.seekg(0, ios::beg);
}

FileDataSource::~FileDataSource() {
  file.close();
}
