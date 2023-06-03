#ifndef SEMESTRAL_COLUMN_VALUE_H
#define SEMESTRAL_COLUMN_VALUE_H

#include <string>
#include <unordered_map>

/**
 * This class is used for cases when we need to quickly access a value in a row by its header name and we have to access it by header names in random order
 * For example, this is useful for boolean expressions in selection expressions
*/
class HeaderValueContainer
{
public:
  HeaderValueContainer(const std::vector<std::string> &header, const std::vector<std::string> & values);
  HeaderValueContainer();
  bool hasHeaderValue(const std::string &headerName) const;
  void addValue(const std::string &headerName, const std::string &value);
  const std::string &operator[](const std::string& headerName) const;
  virtual ~HeaderValueContainer() = default;

private:
  std::unordered_map<std::string, std::string> headerValueMap;
};


#endif // SEMESTRAL_COLUMN_VALUE_H