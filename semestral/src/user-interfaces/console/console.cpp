#include "./console.h"
#include <iostream>
#include <string>
#include "../abstract/exit-exception.h"

using namespace std;

ConsoleInterface::ConsoleInterface() : AbstractInterface() {
  commands.push_back(make_unique<ExitCommand>(memory));
  commands.push_back(make_unique<DeleteVariableCommand>(memory));
  commands.push_back(make_unique<HelpCommand>());
  commands.push_back(make_unique<StoreExpressionToVariable>(memory));
  commands.push_back(make_unique<PrintCommand>(memory));
  commands.push_back(make_unique<PrintVariablesCommand>(memory));
  commands.push_back(make_unique<ExportCommand>(memory));
  commands.push_back(make_unique<SequelizeCommand>(memory));
  commands.push_back(make_unique<UnknownCommand>());
}

void ConsoleInterface::run() {
  cout << "Welcome to the console interface!" << endl;
  cout << "Type \"help\" to see available commands." << endl;
  while (true) {
    string prompt = getNextCommand();
    vector<Token> commandTokens = Tokenizer::getInstnace().tokenize(prompt);
    try { processCommand(commandTokens); }
    catch(ExitException & e){
      break;
    }
    catch (exception &e) {
      cout << e.what() << endl;
    }
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
  for (auto &command : commands) {
    if (command->matchesSyntactically(commandTokens)) {
      command->run(commandTokens);
      return;
    }
  }
}
