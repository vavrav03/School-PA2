#include "./console-command.h"
#include "../../../data-exporters/data-exporters.h"

using namespace std;

ExportCommand::ExportCommand(VariablesMemory &memory) : VariablesDependentCommand(memory) {}

bool ExportCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 4 && command[0].value == "export" && command[2].value == "to" && command[3].quoted;
}

void ExportCommand::run(std::vector<Token> command) {
  string variableName = command[1].value;
  string fileName = command[3].value;
  if (!memory.exists(variableName)) {
    throw runtime_error("Variable " + variableName + " does not exist.");
  }
  shared_ptr<AbstractDataSource>dataSource = memory.get(variableName);
  string extension = fileName.substr(fileName.find_last_of(".") + 1);
  unique_ptr<AbstractDataExporter> exporter;
  if (extension == "csv") {
    exporter = make_unique<CSVDataExporter>(dataSource, fileName);
  } else if (extension == "json") {
    exporter = make_unique<JSONDataExporter>(dataSource, fileName);
  } else {
    throw runtime_error("Unknown file extension " + extension + ".");
  }
  exporter->exportData();
}
