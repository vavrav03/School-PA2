#include "variables-memory.h"

using namespace std;

bool VariablesMemory::exists(const string &name) {
  return variables.find(name) != variables.end();
}

void VariablesMemory::add(const string &name, shared_ptr<AbstractDataSource>item) {
  auto expression = make_shared<DataSourceExpressionWrapper>(item, name);
  variables[name] = expression;
}

shared_ptr<DataSourceExpressionWrapper> VariablesMemory::get(const string &name) {
  return variables[name];
}

vector<string> VariablesMemory::getVariablesNames() {
  vector<string> names;
  for (auto &pair : variables) {
    names.push_back(pair.first);
  }
  return names;
}
