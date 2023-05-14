#ifndef SEMESTRAL_CONSOLE_INTERFACE_H
#define SEMESTRAL_CONSOLE_INTERFACE_H

#include "../abstract/abstract.h"
class ConsoleInterface : public AbstractInterface
{
public:
  ConsoleInterface();
  void run() override;
};

#endif //SEMESTRAL_CONSOLE_INTERFACE_H