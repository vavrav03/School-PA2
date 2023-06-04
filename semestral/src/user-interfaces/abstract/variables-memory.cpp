#include "variables-memory.h"

bool VariablesMemory::exists(const std::string &name) {
  return variables.find(name) != variables.end();
}

void VariablesMemory::add(const std::string &name, AbstractDataSource *item) {
  variables[name] = item;
}

AbstractDataSource *VariablesMemory::get(const std::string &name) {
  return variables[name];
}
