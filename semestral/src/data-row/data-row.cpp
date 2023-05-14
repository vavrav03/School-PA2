
#include "./data-row.h"
#include <string>

using namespace std;

DataRow::DataRow() {}

void DataRow::addField(const string &field)
{
  data.push_back(field);
}

const string &DataRow::operator[](int index) const { return data[index]; }

DataRow::~DataRow()
{
}