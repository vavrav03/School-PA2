#include "variables-memory.h"

using namespace std;

bool VariablesMemory::exists(const string &name) {
  return variables.find(name) != variables.end();
}

void VariablesMemory::add(const string &name, unique_ptr<AbstractDataSource> item) {
  variables[name] = std::move(item);
}

unique_ptr<AbstractDataSource> VariablesMemory::get(const string &name) {
  auto clonedDataSource = variables[name]->clone();
  return clonedDataSource;
}

vector<string> VariablesMemory::getVariablesNames() {
  vector<string> names(variables.size());
  for (auto &pair : variables) {
    names.push_back(pair.first);
  }
  return names;
}
