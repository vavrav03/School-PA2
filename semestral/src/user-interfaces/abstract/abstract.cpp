#include "./abstract.h"
#include "../console/console.h"

AbstractInterface *AbstractInterface::createInstance(const std::string &interfaceName) {
  if (interfaceName == "console") {
    return new ConsoleInterface();
  }
  throw std::runtime_error("Unknown interface: " + interfaceName);
}

