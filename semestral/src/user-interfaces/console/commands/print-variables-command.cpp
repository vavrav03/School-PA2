#include "./console-command.h"

using namespace std;

PrintVariablesCommand::PrintVariablesCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

bool PrintVariablesCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 1 && command[0].value == "vars";
}

void PrintVariablesCommand::run(std::vector<Token> command) {
  vector<string> variablesNames = memory.getVariablesNames();
  for (string &variableName : variablesNames) {
    cout << variableName << endl;
  }
}
