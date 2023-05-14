
#include "./data-row.h"
#include <vector>
#include <string>

using namespace std;

DataRow::DataRow() {}

DataRow::DataRow(const vector<string> &other) : data(other) {}

void DataRow::addField(const string &field)
{
  data.push_back(field);
}

const string &DataRow::operator[](int index) const { return data[index]; }

const int DataRow::size() const { return data.size(); }

DataRow::~DataRow()
{
}