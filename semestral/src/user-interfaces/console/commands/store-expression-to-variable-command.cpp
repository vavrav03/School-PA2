#include "./console-command.h"

using namespace std;

StoreExpressionToVariable::StoreExpressionToVariable(VariablesMemory &memory)
    : VariablesDependentCommand(memory) {

}

bool StoreExpressionToVariable::matchesSyntactically(std::vector<Token> command) {
  return command.size() > 2 && command[1].value == "=";
}

void StoreExpressionToVariable::run(std::vector<Token> command) {
  string variableName = command[0].value;
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  if (memory.exists(variableName)) {
    throw runtime_error("Variable " + variableName + " already exists.");
  }
  vector<Token> expression(command.begin() + 2, command.end());
  unique_ptr<AbstractDataSource> parsedExpression = parser.createExpressionFromTokens(expression);
  memory.add(variableName, std::move(parsedExpression));
}