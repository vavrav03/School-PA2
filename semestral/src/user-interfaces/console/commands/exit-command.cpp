#include "./console-command.h"

using namespace std;

ExitCommand::ExitCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

void ExitCommand::run(std::vector<Token> command) {
  cout << "Exiting..." << endl;
  // TODO: free memory and close files
  exit(0);
}

bool ExitCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 1 && command[0].value == "exit";
}
