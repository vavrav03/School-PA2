#ifndef SEMESTRAL_VARIABLES_MEMORY_H
#define SEMESTRAL_VARIABLES_MEMORY_H

#include <string>
#include <unordered_map>
#include "../../data-sources/abstract/abstract.h"

class VariablesMemory {
public:
  bool exists(const std::string &name);
  void add(const std::string &name, AbstractDataSource *item);
  AbstractDataSource *get(const std::string &name);
  std::vector<std::string> getVariablesNames();

protected:
  std::unordered_map<std::string, AbstractDataSource *> variables;
};


#endif //SEMESTRAL_VARIABLES_MEMORY_H
