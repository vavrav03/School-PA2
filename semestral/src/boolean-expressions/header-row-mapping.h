#ifndef SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_HEADER_ROW_MAP_H_
#define SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_HEADER_ROW_MAP_H_

#include <string>
#include <unordered_map>
#include <vector>

/**
 * Class that provides boolean expressions with access to values in a row of a relational data source. It is created
 * on every new row for selection and theta joins etc...
 */
class HeaderRowMapping {
 public:
  HeaderRowMapping(const std::vector<std::string> &row,
                   const std::unordered_map<std::string, size_t> &indexMap)
      : row(row), indexMap(indexMap) {}

  /**
   *
   * @param name
   * @return either value in row acquired via indexMap using name as key or name itself if name is not in indexMap
   */
  std::string getValue(const std::string &name) const {
    if(indexMap.find(name) == indexMap.end()) {
      return name;
    } else {
      return row.at(indexMap.at(name));
    }
  }
 private:
  const std::vector<std::string> &row;
  const std::unordered_map<std::string, size_t> &indexMap;
};

#endif //SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_HEADER_ROW_MAP_H_
