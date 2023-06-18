#ifndef SEMESTRAL_VARIABLES_MEMORY_H
#define SEMESTRAL_VARIABLES_MEMORY_H

#include <string>
#include <unordered_map>
#include "../../data-sources/abstract.h"
#include "../../data-sources/expressions/expressions.h"

/**
 * Container for relational variables for user interface
 */
class VariablesMemory {
 public:
  bool exists(const std::string &name);
  void add(const std::string &name, std::unique_ptr<AbstractDataSource>&& item);
  std::unique_ptr<AbstractDataSource> get(const std::string &name);
  void erase(const std::string &name);
  std::vector<std::string> getVariablesNames();
 protected:
  std::unordered_map<std::string, std::unique_ptr<AbstractDataSource> > variables;
};

#endif //SEMESTRAL_VARIABLES_MEMORY_H
