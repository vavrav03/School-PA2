#include "./console-command.h"
#include "../../../data-sources/csv/csv.h"
#include "../../../data-sources/json/json.h"

using namespace std;

ImportCommand::ImportCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

bool ImportCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 4 && command[1].value == "=" && command[2].value == "import" && command[3].quoted;
}

void ImportCommand::run(std::vector<Token> command) {
  string variableName = command[0].value;
  string fileName = command[3].value;
  if (memory.exists(variableName)) {
    throw runtime_error("Variable " + variableName + " already exists.");
  }
  string extension = fileName.substr(fileName.find_last_of(".") + 1);
  if (extension == "csv") {
    memory.add(variableName, make_shared<CSVDataSource>(fileName));
  } else if (extension == "json") {
    memory.add(variableName, make_shared<JSONDataSource>(fileName));
  } else {
    throw runtime_error("Unknown file extension " + extension + ".");
  }
}