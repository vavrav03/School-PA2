#include "variables-memory.h"

bool VariablesMemory::exists(const std::string &name) {
  return variables.find(name) != variables.end();
}

void VariablesMemory::add(const std::string &name, AbstractDataSource *item) {
  auto *expression = new NamedDataSourceExpression(item, name);
  variables[name] = expression;
}

NamedDataSourceExpression *VariablesMemory::get(const std::string &name) {
  return variables[name];
}

std::vector<std::string> VariablesMemory::getVariablesNames() {
  std::vector<std::string> names;
  for (auto &pair : variables) {
    names.push_back(pair.first);
  }
  return names;
}
