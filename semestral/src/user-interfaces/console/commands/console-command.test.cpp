#include "./console-command.h"
#include "../tokenizer/tokenizer.h"

#include "../../../../src/test/test_list.h"

using namespace std;

void testImportCommand(Tokenizer &tokenizer) {
  cout << "- RUNNING: testImportCommand" << endl;
  VariablesMemory memory;
  string testFile = string(TEST_ASSETS_DIR) + "test.csv";
  ImportCommand command(memory);
  const string correct1 = "abc = import \"" + testFile + "\"";
  const string correct2 = "ddd=import \"" + testFile + "\"";
  const string incorrectAlreadyExistingVariable = "abc = import \"" + testFile + "\"";
  const string incorrectUnquoted = "abc = import " + testFile;
  const string incorrectWithoutImport = "abc = \"" + testFile + "\"";
  const string incorrectFollowedByCommand = "abc = import \"" + testFile + "\" select * from abc";

  assert(command.matchesSyntactically(tokenizer.tokenize(correct1)));
  command.run(tokenizer.tokenize(correct1));
  assert(memory.get("abc")->getHeaderName(0) == "name");
  assert(memory.get("abc")->getHeaderName(1) == "age");
  assert(memory.get("abc")->getHeaderName(2) == "height");
  vector<string> row = memory.get("abc")->getNextRow();
  assert(row[0] == "John");
  assert(row[1] == "25");
  assert(row[2] == "180");

  assert(command.matchesSyntactically(tokenizer.tokenize(correct2)));
  command.run(tokenizer.tokenize(correct2));
  assert(memory.get("ddd")->getHeaderName(0) == "name");
  assert(memory.get("ddd")->getHeaderName(1) == "age");
  assert(memory.get("ddd")->getHeaderName(2) == "height");
  row = memory.get("ddd")->getNextRow();
  assert(row[0] == "John");
  assert(row[1] == "25");
  assert(row[2] == "180");

  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectUnquoted)));
  try {
    command.run(tokenizer.tokenize(incorrectAlreadyExistingVariable));
    assert(false);
  } catch (exception &e) {
    assert(true);
  }

  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectWithoutImport)));
  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectFollowedByCommand)));
}

void testPrintCommand(Tokenizer &tokenizer) {
  cout << "- RUNNING: testPrintCommand" << endl;
  VariablesMemory memory;
  string testFile = string(TEST_ASSETS_DIR) + "test.csv";
  ImportCommand importCommand(memory);
  importCommand.run(tokenizer.tokenize("abc = import \"" + testFile + "\""));
  PrintCommand command(memory);
  const string correct1 = "print abc";
  const string correct2 = "print abc";
  const string correct3 = "print \"abc\"";
  const string incorrectNonExistingVariable = "print ddd";
  const string incorrectWithoutPrint = "abc";
  const string incorrectMultipleVariables = "print abc ddd";

  assert(command.matchesSyntactically(tokenizer.tokenize(correct1)));
  command.run(tokenizer.tokenize(correct1));

  assert(command.matchesSyntactically(tokenizer.tokenize(correct2)));
  command.run(tokenizer.tokenize(correct2));

  assert(command.matchesSyntactically(tokenizer.tokenize(correct3)));

  assert(command.matchesSyntactically(tokenizer.tokenize(incorrectNonExistingVariable)));
  try {
    command.run(tokenizer.tokenize(incorrectNonExistingVariable));
    assert(false);
  } catch (exception &e) {
    assert(true);
  }

  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectWithoutPrint)));
  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectMultipleVariables)));
}

void testExportCommand(Tokenizer &tokenizer) {
  cout << "- RUNNING: testExportCommand" << endl;
  VariablesMemory memory;
  string testFile = string(TEST_ASSETS_DIR) + "test.csv";
  string outputFile = string(TEST_ASSETS_DIR) + "test_output185212351.csv";
  string testFileJSON = string(TEST_ASSETS_DIR) + "test.json";
  string outputFileJSON = string(TEST_ASSETS_DIR) + "test_output185212352.json";
  ImportCommand importCommand(memory);
  importCommand.run(tokenizer.tokenize("abc = import \"" + testFile + "\""));
  ImportCommand importCommandJSON(memory);
  importCommandJSON.run(tokenizer.tokenize("abcjson = import \"" + testFileJSON + "\""));
  ExportCommand command(memory);
  ExportCommand commandJSON(memory);
  const string correct1 = "export abc to \"" + outputFile + "\"";
  const string correct1JSON = "export abcjson to \"" + outputFileJSON + "\"";
  const string incorrectNonExistingVariable = "export aaa to \"" + outputFile + "\"";
  const string incorrectWithoutExport = "abc to \"" + outputFile + "\"";
  const string incorrectMultipleVariables = "export abc ddd to \"" + outputFile + "\"";
  const string incorrectMulitpleFiles = "export abc to \"" + outputFile + "\" \"" + outputFile + "\"";

  assert(command.matchesSyntactically(tokenizer.tokenize(correct1)));
  command.run(tokenizer.tokenize(correct1));
  // test that file is filled correctly
  ImportCommand importCommandCheck(memory);
  importCommandCheck.run(tokenizer.tokenize("ddd = import \"" + outputFile + "\""));
  assert(memory.get("ddd")->getHeaderName(0) == "name");
  assert(memory.get("ddd")->getHeaderName(1) == "age");
  assert(memory.get("ddd")->getHeaderName(2) == "height");
  vector<string> row = memory.get("ddd")->getNextRow();
  assert(row[0] == "John");
  assert(row[1] == "25");
  assert(row[2] == "180");
  // remove file so that it does not interfere with other tests
  remove(outputFile.c_str());

  assert(commandJSON.matchesSyntactically(tokenizer.tokenize(correct1JSON)));
  commandJSON.run(tokenizer.tokenize(correct1JSON));
  ImportCommand importCommandCheckJSON(memory);
  importCommandCheckJSON.run(tokenizer.tokenize("dddjson = import \"" + outputFileJSON + "\""));
  assert(memory.get("dddjson")->getHeaderName(0) == "a");
  assert(memory.get("dddjson")->getHeaderName(1) == "b");
  assert(memory.get("dddjson")->getHeaderName(2) == "c");
  row = memory.get("dddjson")->getNextRow();
  assert(row[0] == "1");
  assert(row[1] == "2");
  assert(row[2] == "3");
  remove(outputFileJSON.c_str());

  assert(command.matchesSyntactically(tokenizer.tokenize(incorrectNonExistingVariable)));
  try {
    command.run(tokenizer.tokenize(incorrectNonExistingVariable));
    assert(false);
  } catch (exception &e) {
    assert(true);
  }

  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectWithoutExport)));
  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectMultipleVariables)));
  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectMulitpleFiles)));
}

void testSequelizeCommand(Tokenizer & tokenizer){
  cout << "- RUNNING: testSequelizeCommand" << endl;
  VariablesMemory memory;
  string testFile = string(TEST_ASSETS_DIR) + "test.csv";
  ImportCommand importCommand(memory);
  importCommand.run(tokenizer.tokenize("abc = import \"" + testFile + "\""));
  SequelizeCommand command(memory);
  const string correct1 = "sequelize abc";
  const string incorrectNonExistingVariable = "sequelize ddd";
  const string incorrectWithoutSequelize = "abc";

  assert(command.matchesSyntactically(tokenizer.tokenize(correct1)));
  // just test it does not throw
  command.run(tokenizer.tokenize(correct1));

  assert(command.matchesSyntactically(tokenizer.tokenize(incorrectNonExistingVariable)));
  try {
    command.run(tokenizer.tokenize(incorrectNonExistingVariable));
    assert(false);
  } catch (exception &e) {
    assert(true);
  }

  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectWithoutSequelize)));
}

void testConsoleCommands() {
  Tokenizer tokenizer = Tokenizer::createRelgebraInstance();
  testImportCommand(tokenizer);
  testPrintCommand(tokenizer);
  testExportCommand(tokenizer);
  testSequelizeCommand(tokenizer);
}