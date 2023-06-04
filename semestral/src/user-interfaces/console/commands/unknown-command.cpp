#include "./console-command.h"

using namespace std;

UnknownCommand::UnknownCommand() : ConsoleCommand() {}

void UnknownCommand::run(std::vector<Token> command) {
  string commandString = "";
  for (auto token : command) {
    commandString += token.value + " ";
  }
  cout << "Unknown command:\"" + commandString + "\". Type \"help\" to see available commands." << endl;
}

bool UnknownCommand::matchesSyntactically(std::vector<Token> command) {
  return true;
}