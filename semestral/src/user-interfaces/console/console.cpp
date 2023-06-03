#include "./console.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

ConsoleInterface::ConsoleInterface() : AbstractInterface() {
  commands.push_back(new ExitCommand(memory));
  commands.push_back(new HelpCommand());
  commands.push_back(new UnknownCommand());
}

void ConsoleInterface::run() {
  cout << "Welcome to the console interface!" << endl;
  cout << "Type \"help\" to see available commands." << endl;
  while (true) {
    string nextPrompt = getNextCommand();
    vector<Token> commandTokens = tokenize(nextPrompt);
    processCommand(commandTokens);
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

/**
 *
 * @param command
 * @throws std::invalid_argument when closing quote or parenthesis is missing
 *
 * @return
 */
vector<Token> ConsoleInterface::tokenize(const std::string &command) {
  std::vector<Token> tokens;
  std::stringstream ss(command);
  std::string word;
  while (ss >> word) {
    bool quoted = false;
    if (word[0] == '"' && word[word.size() - 1] == '"') {
      quoted = true;
      // remove the quotes
      word = word.substr(1, word.size() - 2);
    }
    if (word.find_first_of("()+-\\") != std::string::npos) {
      // special symbols are considered as separate tokens
      for (char c: word) {
        std::string value(1, c);
        tokens.push_back(Token(value, false));
      }
    } else {
      tokens.push_back(Token(word, quoted));
    }
  }
  return tokens;
}

void ConsoleInterface::processCommand(const vector<Token> &commandTokens) {
  for (auto &command : commands) {
    if (command->shouldRun(commandTokens)) {
      command->run(commandTokens);
      return;
    }
  }
  cout << "Unknown command. Type \"help\" to see available commands." << endl;
}
