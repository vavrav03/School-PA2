#include "./abstract.h"
#include "../console/console.h"

using namespace std;

unique_ptr<AbstractInterface> AbstractInterface::createInstance(const std::string &interfaceName) {
  if (interfaceName == "console") {
    return std::make_unique<ConsoleInterface>();
  }
  throw std::runtime_error("Unknown interface: " + interfaceName);
}

