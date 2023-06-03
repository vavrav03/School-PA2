#ifndef SEMESTRAL_CONSOLE_COMMAND_H
#define SEMESTRAL_CONSOLE_COMMAND_H

#include <string>
#include <vector>
#include "./token.h"
#include <iostream>
#include "../abstract/variables-memory.h"

class ConsoleCommand {

public:
  ConsoleCommand() = default;

  virtual void run(std::vector<Token> command) = 0;
  virtual bool shouldRun(std::vector<Token> command) = 0;
};

class VariablesDependentCommand : public ConsoleCommand {
public:
  explicit VariablesDependentCommand(const VariablesMemory &memory) : ConsoleCommand(), memory(memory) {}

protected:
  const VariablesMemory & memory;
};

class ExitCommand : public VariablesDependentCommand {
public:
  explicit ExitCommand(const VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool shouldRun(std::vector<Token> command) override;
};

class HelpCommand : public ConsoleCommand {
public:
  HelpCommand();

  void run(std::vector<Token> command) override;
  bool shouldRun(std::vector<Token> command) override;
};

class UnknownCommand : public ConsoleCommand {
public:
  UnknownCommand();

  void run(std::vector<Token> command) override;
  bool shouldRun(std::vector<Token> command) override;
};

#endif //SEMESTRAL_CONSOLE_COMMAND_H
