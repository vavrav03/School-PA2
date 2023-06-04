#ifndef SEMESTRAL_VARIABLES_MEMORY_H
#define SEMESTRAL_VARIABLES_MEMORY_H

#include <string>
#include <unordered_map>
#include "../../data-sources/abstract.h"
#include "../../data-sources/expressions/expressions.h"


class VariablesMemory {
public:
  bool exists(const std::string &name);
  void add(const std::string &name, AbstractDataSource *item);
  NamedDataSourceExpression *get(const std::string &name);
  std::vector<std::string> getVariablesNames();

protected:
  std::unordered_map<std::string, NamedDataSourceExpression *> variables;
};


#endif //SEMESTRAL_VARIABLES_MEMORY_H
