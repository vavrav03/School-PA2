#include "./console-command.h"

DeleteVariableCommand::DeleteVariableCommand(VariablesMemory &memory)
    : VariablesDependentCommand(memory) {}

bool DeleteVariableCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 2 && command[0].value == "delete";
}

void DeleteVariableCommand::run(std::vector<Token> command) {
  if (!memory.exists(command[1].value)) {
    throw std::invalid_argument("Variable does not exist");
  }

  memory.get(command[1].value);
  memory.erase(command[1].value);
}