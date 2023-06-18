#ifndef SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_HEADER_ROW_MAP_H_
#define SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_HEADER_ROW_MAP_H_

#include <string>
#include <unordered_map>
#include <vector>

class HeaderRowMapping {
 public:
  HeaderRowMapping(const std::vector<std::string> &row,
                   const std::unordered_map<std::string, size_t> &indexMap)
      : row(row), indexMap(indexMap) {}

  std::string getValue(const std::string &name) const {
    return row.at(indexMap.at(name));
  }
 private:
  const std::vector<std::string> &row;
  const std::unordered_map<std::string, size_t> &indexMap;
};

#endif //SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_HEADER_ROW_MAP_H_
