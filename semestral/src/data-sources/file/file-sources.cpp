#include "./file-sources.h"
#include "../../utils/utils.h"

using namespace std;

FileDataSource::FileDataSource(const std::string &path) : file(path) {
  if (file.fail()) {
    throw runtime_error("File not found");
  }
}

vector<string> FileDataSource::getHeaderVector() const {
  return indexMapToVector(this->header);
}

unordered_map<string, size_t> FileDataSource::getHeaderMap() const {
  return this->header;
}

size_t FileDataSource::getHeaderIndex(const string &name) const {
  return this->header.at(name);
}

const string & FileDataSource::getHeaderName(size_t index) const {
  for(auto &pair: this->header){
    if(pair.second == index){
      return pair.first;
    }
  }
  throw runtime_error("Index not found");
}

size_t FileDataSource::getHeaderSize() const {
  return this->header.size();
}

void FileDataSource::reset() {
  file.clear();
  file.seekg(0, ios::beg);

}

FileDataSource::~FileDataSource() {
  file.close();
}

