#include "./console-command.h"

using namespace std;

PrintCommand::PrintCommand(VariablesMemory &memory, const RelationalExpressionParser &parser)
    : VariablesDependentCommand(memory), parser(parser) {}

bool PrintCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() >= 2 && command[0].value == "print";
}

void PrintCommand::run(std::vector<Token> command) {
  string variableName = command[1].value;
  unique_ptr<AbstractDataSource> dataSource;
  if (command.size() == 2) {
    if (!memory.exists(variableName)) {
      throw runtime_error("Variable " + variableName + " does not exist.");
    }
    dataSource = memory.get(variableName);
  } else {
    vector<Token> expression(command.begin() + 2, command.end());
    dataSource = parser.createExpressionFromTokens(expression);
  }
  dataSource->reset();
  cout << "| ";
  for (string &columnName : dataSource->getHeaderVector()) {
    cout << columnName << " | ";
  }
  cout << endl;
  vector<string> row;
  while (!(row = dataSource->getNextRow()).empty()) {
    cout << "| ";
    for (string &value : row) {
      cout << value << " | ";
    }
    cout << endl;
  }
}
