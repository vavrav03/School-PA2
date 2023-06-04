#include "abstract.h"
#include "../utils/utils.h"

using namespace std;

AbstractDataSource::AbstractDataSource() = default;

AbstractDataSource::~AbstractDataSource() = default;

FileDataSource::FileDataSource(const std::string &path) : file(path) {
  if (file.fail()) {
    throw runtime_error("File not found");
  }
}

vector<string> FileDataSource::getHeaderVector() const {
  return indexMapToVector(this->header);
}

unordered_map<string, int> FileDataSource::getHeaderMap() const {
  return this->header;
}

int FileDataSource::getHeaderIndex(const string &name) const {
  return this->header.at(name);
}

const string & FileDataSource::getHeaderName(int index) const {
  for(auto &pair: this->header){
    if(pair.second == index){
      return pair.first;
    }
  }
  throw runtime_error("Index not found");
}

int FileDataSource::getHeaderSize() const {
  return this->header.size();
}

void FileDataSource::reset() {
  file.clear();
  file.seekg(0, ios::beg);

}

FileDataSource::~FileDataSource() {
  file.close();
}

