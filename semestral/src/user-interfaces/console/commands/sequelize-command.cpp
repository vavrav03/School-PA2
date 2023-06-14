#include "./console-command.h"

using namespace std;

SequelizeCommand::SequelizeCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

bool SequelizeCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() >= 2 && command[0].value == "sequelize";
}

void SequelizeCommand::run(std::vector<Token> command) {
  if (command.size() == 2) {
    if (!memory.exists(command[1].value)) {
      throw runtime_error("Variable " + command[1].value + " does not exist.");
    }
    unique_ptr<AbstractDataSource> dataSource = memory.get(command[1].value);
    cout << dataSource->toSQL() << endl;
  } else {
    // TODO: convert expression directly to SQL
  }
}
