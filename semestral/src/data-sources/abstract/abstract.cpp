#include "abstract.h"

using namespace std;

AbstractDataSource::AbstractDataSource() = default;

const DataRow &AbstractDataSource::getHeader() const {
  return this->header;
}

const int AbstractDataSource::getHeaderSize() const {
  return this->header.size();
}

AbstractDataSource::~AbstractDataSource() = default;