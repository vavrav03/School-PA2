#include "./console.h"
#include <iostream>
#include <string>

using namespace std;

ConsoleInterface::ConsoleInterface() : AbstractInterface(), tokenizer(Tokenizer::createRelgebraInstance()),
                                       stringToRelationParser(
                                           RelationalExpressionParser::createDefaultInstance(tokenizer, memory)) {
  commands.push_back(make_unique<ExitCommand>(memory));
  commands.push_back(make_unique<HelpCommand>());
  commands.push_back(make_unique<ImportCommand>(memory));
  commands.push_back(make_unique<StoreExpressionToVariable>(memory, stringToRelationParser));
  commands.push_back(make_unique<PrintCommand>(memory, stringToRelationParser));
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
  for (auto &command : commands) {
    if (command->matchesSyntactically(commandTokens)) {
      command->run(commandTokens);
      return;
    }
  }
}
