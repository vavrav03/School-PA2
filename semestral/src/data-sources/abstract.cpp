#include "abstract.h"
#include "../utils/utils.h"

using namespace std;

AbstractDataSource::AbstractDataSource() = default;

vector<string> AbstractDataSource::getHeader() const {
  return indexMapToVector(this->header);
}

int AbstractDataSource::getHeaderIndex(const string &name) const {
  return this->header.at(name);
}

const string & AbstractDataSource::getHeaderName(int index) const {
  for(auto &pair: this->header){
    if(pair.second == index){
      return pair.first;
    }
  }
  throw runtime_error("Index not found");
}

int AbstractDataSource::getHeaderSize() const {
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
