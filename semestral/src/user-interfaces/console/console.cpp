#include "./console.h"
#include <iostream>
#include <string>

using namespace std;

ConsoleInterface::ConsoleInterface() : AbstractInterface(), tokenizer(Tokenizer::createRelgebraInstance()) {
  commands.push_back(new ExitCommand(memory));
  commands.push_back(new HelpCommand());
  commands.push_back(new ImportCommand(memory));
  commands.push_back(new PrintCommand(memory));
  commands.push_back(new PrintVariablesCommand(memory));
  commands.push_back(new ExportCommand(memory));
  commands.push_back(new UnknownCommand());
}

void ConsoleInterface::run() {
  cout << "Welcome to the console interface!" << endl;
  cout << "Type \"help\" to see available commands." << endl;
  while (true) {
    string prompt = getNextCommand();
    vector<Token> commandTokens = tokenizer.tokenize(prompt);
    try { processCommand(commandTokens); }
    catch (exception &e) { cout << e.what() << endl; }
  }
}

string ConsoleInterface::getNextCommand() {
  string command;
  printPrompt();
  getline(cin, command);
  return command;
}

void ConsoleInterface::printPrompt() {
  cout << "> ";
}

void ConsoleInterface::processCommand(const vector<Token> &commandTokens) {
  for (auto &command: commands) {
    if (command->matchesSyntactically(commandTokens)) {
      command->run(commandTokens);
      return;
    }
  }
}
