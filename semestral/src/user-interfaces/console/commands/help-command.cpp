#include "console-command.h"

using namespace std;

HelpCommand::HelpCommand() : ConsoleCommand() {}

bool HelpCommand::matchesSyntactically(std::vector<Token> command) {
  return command.size() == 1 && !command[0].quoted && command[0].value == "help";
}

// @formatter:off
void HelpCommand::run(std::vector<Token> command) {
  cout << R"(App specific commands)" << endl;
  cout << R"(   - exit: Exits the program.)" << endl;
  cout << R"(   - export ... to ...: Creates a file filled by a content of a variable)" << endl;
  cout << R"(       - export <variable_name> to "<file_name>.csv" exports a content of a <variable_name> variable to a CSV file)" << endl;
  cout << R"(       - export <variable_name> to "<file_name>.json" exports a content of a <variable_name> variable to a JSON file)" << endl;
  cout << R"(   - help: Prints this help.)" << endl;
  cout << R"(   - print: prints a content of an attached data source plus its header to console)" << endl;
  cout << R"(       - print <variable_name>)" << endl;
  cout << R"(       - print <expression>)" << endl;
  cout << R"(   - sequelize: Prints a content of a variable to console in a sequelize format)" << endl;
  cout << R"(   - <variable name> = <expression>: Attaches data source to a given variable)" << endl;
  cout << R"(       - <variable_name> = "<file_path>.csv" - attaches CSV file. Must be in quotes with .csv extension)" << endl;
  cout << R"(       - <variable_name> = "<file_path>.json" returns JSON datasource and sets it to a <variable_name> variable)" << endl;
  cout << R"(       - <variable_name> = <expression> - attaches result of an expression to a <variable_name> variable)" << endl;
  cout << R"(   - vars: Prints a list of all variables)" << endl;
  cout << R"(other operations follow standard relational algebra syntax:)" << endl;
  cout << R"(   - set-set operations: union "∪", intersect "∩", except "\", cross "×", divide "÷")" << endl;
  cout << R"(   - set-boolean operations: is_subset "⊆", equals "=", is_proper_subset "⊂")" << endl;
  cout << R"(   - general joins: join "[rel1.col1 < rel2.col3]", left_semi_join "<condition]", right_semi_join "[condition>", left_anti_join "!<condition]", right_anti_join "![condition>")" << endl;
  cout << R"(   - natural joins (same order as general joins): "*", "<*", "*>", "!<*", "!*>")" << endl;
  cout << R"(   - boolean operations: and "∧", or "∨", not "¬")" << endl;
  cout << R"(   - projection: project "relation[col1, col3]")" << endl;
  cout << R"(   - selection: select "(condition)" << endl;
  cout << R"(   - rename: rename "relation[col1 -> new_col1, col3 -> new_col3]")" << endl;
  cout << R"(General syntax rules:)" << endl;
  cout << R"(   - all operations are case insensitive)" << endl;
  cout << R"(   - {} can be used to redefine priority for relational expressions and () for boolean expressions)" << endl;
  cout << R"(   - implicit operator priorities are implemented. Left to right evaluation is used)" << endl;
  cout << R"(   - use quotes when dealing with file names. Otherwise, they are not going to be considered file names)" << endl;
  cout << R"(   - write date in format "YYYY-MM-DD")" << endl;
  cout << R"(Example:)" << endl;
  cout << R"(   animals1 = "animals1.csv")" << endl;
  cout << R"(   animals2 = "animals2.csv")" << endl;
  cout << R"(   nourishment = "nourishment.csv")" << endl;
  cout << R"(   temp = {{animals1 ∪ animals2} × nourishment})" << endl;
  cout << R"(   print temp)" << endl;
  cout << R"(   sequelize temp)" << endl;
  cout << R"(   export temp to "temp.csv")" << endl;
}
// @formatter:on