#include "variables-memory.h"

using namespace std;

bool VariablesMemory::exists(const string &name) {
  return variables.find(name) != variables.end();
}

void VariablesMemory::add(const string &name, shared_ptr<AbstractDataSource>item) {
  variables[name] = item;
}

shared_ptr<AbstractDataSource> VariablesMemory::get(const string &name) {
  return variables[name];
}

vector<string> VariablesMemory::getVariablesNames() {
  vector<string> names;
  for (auto &pair : variables) {
    names.push_back(pair.first);
  }
  return names;
}

string VariablesMemory::getAvailableAlias(const string &preferredAlias) {
  string alias = preferredAlias;
  if(!this->exists(preferredAlias)) {
    return alias;
  }
  alias += "_a";
  while(this->exists(alias)) {
    if(alias.back() == 'z') {
      alias += 'a';
    } else {
      alias.back()++;
    }
  }
  return alias;
}

string VariablesMemory::generateNewAvailableAlias(const string & startingPoint) {
  if(startingPoint.empty()) {
    return "a";
  }
  string alias = startingPoint;
  do {
    if(alias.back() == 'z') {
      alias += 'a';
    } else {
      alias.back()++;
    }
  } while(this->exists(alias));
  return alias;
}
