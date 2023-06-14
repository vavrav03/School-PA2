#ifndef SEMESTRAL_ABSTRACT_INTERFACE_H
#define SEMESTRAL_ABSTRACT_INTERFACE_H

#include <string>
#include "./variables-memory.h"

class AbstractInterface {
 public:
  virtual void run() = 0;
  static std::unique_ptr<AbstractInterface> createInstance(const std::string &interfaceName);
  virtual ~AbstractInterface() = default;
  VariablesMemory memory;
};

#endif //SEMESTRAL_ABSTRACT_INTERFACE_H
