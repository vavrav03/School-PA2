
#include "./data-row.h"

DataRow::DataRow() {}

void DataRow::addField(const DataType *field) {
  data.push_back(field->clone());
}

DataType *DataRow::operator[](int index) const { return data[index]; }

DataRow::~DataRow() {
  for (auto field : data) {
    delete field;
  }
}