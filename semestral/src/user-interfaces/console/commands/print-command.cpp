#include "./console-command.h"

using namespace std;

PrintCommand::PrintCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

bool PrintCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 2 && command[0].value == "print";
}

void PrintCommand::run(std::vector<Token> command) {
  string variableName = command[1].value;
  if (!memory.exists(variableName)) {
    throw runtime_error("Variable " + variableName + " does not exist.");
  }
  NamedDataSourceExpression *dataSource = memory.get(variableName);
  dataSource->reset();
  cout << "| ";
  for (string columnName: dataSource->getHeaderVector()) {
    cout << columnName << " | ";
  }
  cout << endl;
  while (dataSource->hasNextRow()) {
    vector<string> row = dataSource->getNextRow();
    cout << "| ";
    for (string &value: row) {
      cout << value << " | ";
    }
    cout << endl;
  }
}
