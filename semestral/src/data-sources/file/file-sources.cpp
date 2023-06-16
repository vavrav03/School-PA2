#include "./file-sources.h"
#include "../../utils/utils.h"

using namespace std;

FileDataSource::FileDataSource(const std::string &path) : AbstractDataSource(), file(path), path(path) {
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

const string &FileDataSource::getHeaderName(size_t index) const {
  return findValueOrThrowInIndexMap(this->header, index);
}

size_t FileDataSource::getHeaderSize() const {
  return this->header.size();
}

string FileDataSource::toSQL() const {
  return "SELECT * FROM " + getNameWithoutExtension(path);
}

void FileDataSource::reset() {
  file.clear();
  file.seekg(0, ios::beg);
}
