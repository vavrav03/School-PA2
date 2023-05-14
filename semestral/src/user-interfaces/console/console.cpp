#include "./console.h"
#include <iostream>
#include <string>

using namespace std;

ConsoleInterface::ConsoleInterface() : AbstractInterface()
{
}

void ConsoleInterface::run()
{
  cout << "Welcome to the console interface!" << endl;
  cout << "Type \"help\" to see available commands." << endl;
  while (true)
  {
    string command = getNextCommand();
    processCommand(command);
  }
}

string ConsoleInterface::getNextCommand()
{
  string command;
  printPrompt();
  getline(cin, command);
  return command;
}

void ConsoleInterface::processCommand(const string &command)
{
  if (command == "help")
  {
    printHelp();
  }
  else if (command == "exit")
  {
    processExit();
  }
  else
  {
    processUnknownCommand(command);
  }
}

void ConsoleInterface::printHelp()
{
  cout << "App specific commands" << endl;
  cout << "   - help: Prints this help." << endl;
  cout << "   - exit: Exits the program." << endl;
  cout << "   - import: Imports a file to a new or existing variable" << endl;
  cout << "       - <variable_name> = import \"<file_name>.csv\" returns CSV datasource and sets it to a <variable_name> variable" << endl;
  cout << "       - <variable_name> = import \"<file_name>.json\" returns JSON datasource and sets it to a <variable_name> variable" << endl;
  cout << "   - export ... to ...: Creates a file filled by a content of a variable" << endl;
  cout << "       - export <variable_name> to \"<file_name>.csv\" exports a content of a <variable_name> variable to a CSV file" << endl;
  cout << "       - export <variable_name> to \"<file_name>.json\" exports a content of a <variable_name> variable to a JSON file" << endl;
  cout << "   - print: Prints a content of a variable to console" << endl;
  cout << "other operations follow standard relational algebra syntax:" << endl;
  cout << "   - set-set operations: union \"∪\", intersect \"∩\", except \"\\\", cross \"×\", divide \"÷\"" << endl;
  cout << "   - set-boolean operations: is_subset \"⊆\", equals \"=\", is_proper_subset \"⊂\"" << endl;
  cout << "   - general joins: join \"[rel1.col1 < rel2.col3]\", left_semi_join \"<condition]\", right_semi_join \"[condition>\", left_anti_join \"!<condition]\", right_anti_join \"![condition>\"" << endl;
  cout << "   - natural joins (same order as general joins): \"*\", \"<*\", \"*>\", \"!<*\", \"!*>\"" << endl;
  cout << "   - boolean operations: and \"∧\", or \"∨\", not \"¬\"" << endl;
  cout << "   - projection: project \"relation[col1, col3]\"" << endl;
  cout << "   - selection: select \"(condition)\"" << endl;
  cout << "   - rename: rename \"relation[col1 -> new_col1, col3 -> new_col3]\"" << endl;
  cout << "General syntax rules:" << endl;
  cout << "   - all operations are case insensitive" << endl;
  cout << "   - \"(\" \")\" can be used to redefine priority" << endl;
  cout << "   - no implicit operator priorities are implemented. You have to explicitly define priority by using \"(\" \")\". Left to right evaluation is used" << endl;
  cout << "   - write date in format \"YYYY-MM-DD\" to ensure correct comparison" << endl;
  cout << "   - write time in format \"HH:MM:SS\" to ensure correct comparison" << endl;
  cout << "   - write timestamp in format \"YYYY-MM-DD HH:MM:SS\" to ensure correct comparison" << endl;
}

void ConsoleInterface::processExit()
{
  cout << "Exiting..." << endl;
  // TODO: free memory and close files
  exit(0);
}

void ConsoleInterface::processUnknownCommand(const string &command)
{
  cout << "Unknown command:\"" + command + "\". Type \"help\" to see available commands." << endl;
}

void ConsoleInterface::printPrompt()
{
  cout << "> ";
}