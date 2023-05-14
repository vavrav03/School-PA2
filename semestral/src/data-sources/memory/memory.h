#ifndef SEMESTRAL_MEMORY_DATA_SOURCE_H
#define SEMESTRAL_MEMORY_DATA_SOURCE_H

#include "./variable.h"
#include <unordered_map>
#include <string>

class MemoryDataSource {
public:
  MemoryDataSource();

  void createVariable(const std::string &name);
  void createVariable(const std::string &name, const AbstractDataSource &dataSource);
  VariableDataSource &getVariableDataSource(const std::string &name);
  
private:
  std::unordered_map<std::string, VariableDataSource> header;
};

#endif // SEMESTRAL_MEMORY_DATA_SOURCE_H