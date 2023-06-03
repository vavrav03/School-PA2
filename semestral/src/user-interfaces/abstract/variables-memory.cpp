#include "variables-memory.h"

bool VariablesMemory::existsVariable(const std::string &name) {
  return variables.find(name) != variables.end();
}

void VariablesMemory::addVariable(const std::string &name, AbstractDataSource *item) {
  variables[name] = item;
}
