#include "./console-command.h"
#include "../../../data-sources/file/csv.h"
#include "../../../data-sources/file/json.h"

using namespace std;

ImportCommand::ImportCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

bool ImportCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 4 && command[1].value == "=" && command[2].value == "import" && command[3].quoted;
}

void ImportCommand::run(std::vector<Token> command) {
  string variableName = command[0].value;
  string filePath = command[3].value;
  if (memory.exists(variableName)) {
    throw runtime_error("Variable " + variableName + " already exists.");
  }
  string extension = getExtensionFromPath(filePath);
  string fileName = getNameWithoutExtension(filePath);
  string alias = memory.getAvailableAlias(fileName);
  if (extension == "csv") {
    memory.add(variableName, make_unique<CSVDataSource>(filePath, alias));
  } else if (extension == "json") {
    memory.add(variableName, make_unique<JSONDataSource>(filePath, alias));
  } else {
    throw runtime_error("Unknown file extension " + extension + ".");
  }
}