
#include "./header-value-container.h"

using namespace std;

HeaderValueContainer::HeaderValueContainer(DataRow &header, DataRow &values)
{
  for (int i = 0; i < header.size(); i++)
  {
    this->headerValueMap[header[i]] = values[i];
  }
}

const bool HeaderValueContainer::hasHeaderValue(const string &headerName) const
{
  return this->headerValueMap.find(headerName) != this->headerValueMap.end();
}

const string &HeaderValueContainer::operator[](const string&headerName) const
{ 
  return this->headerValueMap.at(headerName);
}