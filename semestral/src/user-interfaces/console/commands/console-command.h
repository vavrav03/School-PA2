#ifndef SEMESTRAL_CONSOLE_COMMAND_H
#define SEMESTRAL_CONSOLE_COMMAND_H

#include <string>
#include <vector>
#include "../tokenizer/token.h"
#include <iostream>
#include "../../abstract/variables-memory.h"

class ConsoleCommand {

public:
  ConsoleCommand() = default;

  virtual void run(std::vector<Token> command) = 0;
  virtual bool matchesSyntactically(std::vector<Token> command) = 0;
};

class VariablesDependentCommand : public ConsoleCommand {
public:
  explicit VariablesDependentCommand(VariablesMemory &memory) : ConsoleCommand(), memory(memory) {}

protected:
  VariablesMemory & memory;
};

class ExitCommand : public VariablesDependentCommand {
public:
  explicit ExitCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class HelpCommand : public ConsoleCommand {
public:
  HelpCommand();

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class UnknownCommand : public ConsoleCommand {
public:
  UnknownCommand();

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class ImportCommand : public VariablesDependentCommand {
public:
  explicit ImportCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class PrintCommand: public VariablesDependentCommand {
public:
  explicit PrintCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class PrintVariablesCommand: public VariablesDependentCommand {
public:
  explicit PrintVariablesCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

#endif //SEMESTRAL_CONSOLE_COMMAND_H
