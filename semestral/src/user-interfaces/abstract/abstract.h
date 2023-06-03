#ifndef SEMESTRAL_ABSTRACT_INTERFACE_H
#define SEMESTRAL_ABSTRACT_INTERFACE_H

#include <string>
#include "./variables-memory.h"

class AbstractInterface
{
public:
  virtual void run() = 0;
  static AbstractInterface *createInstance(const std::string &interfaceName);
  VariablesMemory memory;
};

#endif //SEMESTRAL_ABSTRACT_DATA_SOURCE_H
