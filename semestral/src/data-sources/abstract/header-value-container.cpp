
#include "./header-value-container.h"

using namespace std;

HeaderValueContainer::HeaderValueContainer(const vector<string> &header, const vector<string> &values)
{
  for (int i = 0; i < header.size(); i++)
  {
    this->headerValueMap[header[i]] = values[i];
  }
}

bool HeaderValueContainer::hasHeaderValue(const string &headerName) const
{
  return this->headerValueMap.find(headerName) != this->headerValueMap.end();
}

const string &HeaderValueContainer::operator[](const string&headerName) const
{ 
  return this->headerValueMap.at(headerName);
}