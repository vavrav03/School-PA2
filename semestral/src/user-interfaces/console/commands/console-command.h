#ifndef SEMESTRAL_CONSOLE_COMMAND_H
#define SEMESTRAL_CONSOLE_COMMAND_H

#include <string>
#include <vector>
#include <iostream>
#include "../../abstract/variables-memory.h"
#include "../../string-parsing/tokenizer/token.h"
#include "../../string-parsing/tokenizer/tokenizer.h"
#include "../../string-parsing/expression-parser.h"

/**
 * Abstract class for all commands used by console interface
 */
class ConsoleCommand {

 public:
  ConsoleCommand() = default;

  virtual void run(std::vector<Token> command) = 0;
  virtual bool matchesSyntactically(std::vector<Token> command) = 0;
  virtual ~ConsoleCommand() = default;
};

/**
 * Abstract class for all commands that need access to variables memory
 */
class VariablesDependentCommand : public ConsoleCommand {
 public:
  explicit VariablesDependentCommand(VariablesMemory &memory) : ConsoleCommand(), memory(memory) {}

 protected:
  VariablesMemory &memory;
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

class PrintCommand : public VariablesDependentCommand {
 public:
  explicit PrintCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
 private:
};

class PrintVariablesCommand : public VariablesDependentCommand {
 public:
  explicit PrintVariablesCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class ExportCommand : public VariablesDependentCommand {
 public:
  explicit ExportCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class SequelizeCommand : public VariablesDependentCommand {
 public:
  explicit SequelizeCommand(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

class StoreExpressionToVariable : public VariablesDependentCommand {
 public:
  explicit StoreExpressionToVariable(VariablesMemory &memory);

  void run(std::vector<Token> command) override;
  bool matchesSyntactically(std::vector<Token> command) override;
};

#endif //SEMESTRAL_CONSOLE_COMMAND_H
