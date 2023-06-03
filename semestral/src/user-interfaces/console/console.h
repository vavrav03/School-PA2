#ifndef SEMESTRAL_CONSOLE_INTERFACE_H
#define SEMESTRAL_CONSOLE_INTERFACE_H

#include "../abstract/variables-memory.h"

#include "./token.h"
#include "./console-command.h"
#include "../abstract/abstract.h"
#include "./tokenizer/tokenizer.h"

class ConsoleInterface : public AbstractInterface
{
public:
  ConsoleInterface();
  void run() override;
private:
  std::string getNextCommand();
  void processCommand(const std::vector<Token> &commandTokens);
  void printPrompt();
  std::vector<ConsoleCommand *> commands;
  Tokenizer tokenizer;
};

#endif //SEMESTRAL_CONSOLE_INTERFACE_H