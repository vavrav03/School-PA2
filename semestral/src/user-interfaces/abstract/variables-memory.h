#ifndef SEMESTRAL_VARIABLES_MEMORY_H
#define SEMESTRAL_VARIABLES_MEMORY_H

#include <string>
#include <unordered_map>
#include "../../data-sources/abstract/abstract.h"

class VariablesMemory {
public:
  bool existsVariable(const std::string &name);
  void addVariable(const std::string &name, AbstractDataSource *item);
protected:
  std::unordered_map<std::string, AbstractDataSource *> variables;
};


#endif //SEMESTRAL_VARIABLES_MEMORY_H
