#ifndef SEMESTRAL_COLUMN_VALUE_H
#define SEMESTRAL_COLUMN_VALUE_H

#include <string>
#include <unordered_map>
#include "./data-row.h"

/**
 * This class is used for cases when we need to quickly access a value in a row by its header name and we have to access it by header names in random order
 * For example, this is useful for boolean expressions in selection expressions
*/
class HeaderValueContainer
{
public:
  HeaderValueContainer(DataRow &header, DataRow & values);
  const bool hasHeaderValue(const std::string &headerName) const;
  const std::string &operator[](const std::string& headerName) const;
  virtual ~HeaderValueContainer() = default;

private:
  std::unordered_map<std::string, std::string> headerValueMap;
};


#endif // SEMESTRAL_COLUMN_VALUE_H