#include "./console-command.h"

using namespace std;

PrintCommand::PrintCommand(VariablesMemory &memory)
    : VariablesDependentCommand(memory) {}

bool PrintCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() >= 2 && command[0].value == "print";
}

void PrintCommand::run(std::vector<Token> command) {
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> dataSource;
  const vector<Token> expression(command.begin() + 1, command.end());
  dataSource = parser.createExpressionFromTokens(expression);
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
