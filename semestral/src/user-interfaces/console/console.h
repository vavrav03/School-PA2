#ifndef SEMESTRAL_CONSOLE_INTERFACE_H
#define SEMESTRAL_CONSOLE_INTERFACE_H

#include "../abstract/abstract.h"
class ConsoleInterface : public AbstractInterface
{
public:
  ConsoleInterface();
  void run() override;
  void printHelp();
private:
  std::string getNextCommand();
  void processCommand(const std::string & command);
  void processUnknownCommand(const std::string & command);
  void processExit();
  void printPrompt();
};

#endif //SEMESTRAL_CONSOLE_INTERFACE_H