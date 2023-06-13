#ifndef SEMESTRAL_VARIABLES_MEMORY_H
#define SEMESTRAL_VARIABLES_MEMORY_H

#include <string>
#include <unordered_map>
#include "../../data-sources/abstract.h"
#include "../../data-sources/expressions/expressions.h"

class VariablesMemory {
 public:
  bool exists(const std::string &name);
  void add(const std::string &name, std::shared_ptr<AbstractDataSource> item);
  std::shared_ptr<AbstractDataSource> get(const std::string &name);
  std::vector<std::string> getVariablesNames();

  /**
   *
   * @param preferredAlias if this name is available, it will be returned. If not, it will be used as a prefix.
   * @return name that is available to be used as a variable name and is based on the preferredAlias
   */
  std::string getAvailableAlias(const std::string &preferredAlias);
  std::string generateNewAvailableAlias(const std::string &startingPoint);

 protected:
  std::unordered_map<std::string, std::shared_ptr<AbstractDataSource> > variables;
};

#endif //SEMESTRAL_VARIABLES_MEMORY_H
