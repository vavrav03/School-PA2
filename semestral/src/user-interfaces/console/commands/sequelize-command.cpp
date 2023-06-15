#include "./console-command.h"

using namespace std;

SequelizeCommand::SequelizeCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

bool SequelizeCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() >= 2 && command[0].value == "sequelize";
}

void SequelizeCommand::run(std::vector<Token> command) {
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  vector<Token> expression(command.begin() + 1, command.end());
  unique_ptr<AbstractDataSource> parsedExpression = parser.createExpressionFromTokens(expression);
  cout << parsedExpression->toSQL() << endl;
}
