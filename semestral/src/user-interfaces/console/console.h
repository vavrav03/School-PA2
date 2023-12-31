#ifndef SEMESTRAL_CONSOLE_INTERFACE_H
#define SEMESTRAL_CONSOLE_INTERFACE_H

#include "../variables-memory/variables-memory.h"

#include "./commands/console-command.h"
#include "../abstract/abstract.h"
#include "../string-parsing/tokenizer/token.h"
#include "../string-parsing/tokenizer/tokenizer.h"
#include "../../expression-evaluation/expression-evaluator.h"

/**
 * Interface for interaction with user via command line
 */
class ConsoleInterface : public AbstractInterface {
 public:
  ConsoleInterface();
  /**
   * Wait in endless loop for next command separated by new line. Command is then tokenized and passed to processCommand
   */
  void run() override;
  ~ConsoleInterface() override = default;
 private:

  /**
   * Wait until user enters a command and return it
   * @return unparsed command
   */
  std::string getNextCommand();

  /**
   * Processes given command. If command is not recognized, UnknownCommand is used
   * @param commandTokens
   */
  void processCommand(const std::vector<Token> &commandTokens);
  void printPrompt();

  /**
   * List of all available commands
   */
  std::vector<std::unique_ptr<ConsoleCommand> > commands;
};

#endif //SEMESTRAL_CONSOLE_INTERFACE_H