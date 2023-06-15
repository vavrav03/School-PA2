#include "../user-interfaces/console/commands/console-command.h"
#include "../user-interfaces/string-parsing/tokenizer/tokenizer.h"

#include "test.h"

using namespace std;

void testStoreToVariableCommand() {
  cout << "- RUNNING: testStoreToVariableCommand" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  string testFile = string(TEST_CSV_1);
  const string correct1 = "abc = \"" + testFile + "\"";
  const string correct2 = "ddd=\"" + testFile + "\"";
  const string incorrectAlreadyExistingVariable = "abc = \"" + testFile + "\"";

  assert(runStoreToMemory(memory, tokenizer.tokenize(correct1)));
  assert(memory.get("abc")->getHeaderName(0) == "name");
  assert(memory.get("abc")->getHeaderName(1) == "age");
  assert(memory.get("abc")->getHeaderName(2) == "height");
  vector<string> row = memory.get("abc")->getNextRow();
  assert(row[0] == "John");
  assert(row[1] == "25");
  assert(row[2] == "180");

  assert(runStoreToMemory(memory, tokenizer.tokenize(correct2)));
  assert(memory.get("ddd")->getHeaderName(0) == "name");
  assert(memory.get("ddd")->getHeaderName(1) == "age");
  assert(memory.get("ddd")->getHeaderName(2) == "height");
  row = memory.get("ddd")->getNextRow();
  assert(row[0] == "John");
  assert(row[1] == "25");
  assert(row[2] == "180");


  try {
    runStoreToMemory(memory, tokenizer.tokenize(incorrectAlreadyExistingVariable));
    assert(false);
  } catch (exception &e) {
    assert(true);
  }
}

void testPrintCommand() {
  cout << "- RUNNING: testPrintCommand" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  string testFile = string(TEST_CSV_1);
  runStoreToMemory(memory, tokenizer.tokenize("abc = \"" + testFile + "\""));
  PrintCommand command(memory);
  const string correct1 = "print abc";
  const string correct2 = "print abc";
  const string correct3 = "print \"abc\"";
  const string correct4 = "print {{{abc[name]}}}";
  const string incorrectNonExistingVariable = "print ddd";
  const string incorrectWithoutPrint = "abc";
  const string incorrectExpression = "print abc[";

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

  try {
    command.run(tokenizer.tokenize(incorrectExpression));
    assert(false);
  } catch (exception &e) {
    assert(true);
  }

  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectWithoutPrint)));
  assert(!command.matchesSyntactically(tokenizer.tokenize(incorrectWithoutPrint)));
}

void testExportCommand() {
  cout << "- RUNNING: testExportCommand" << endl;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  VariablesMemory memory;
  string testFile = string(TEST_CSV_1);
  string outputFile = string(TEST_ASSETS_DIR) + "test_output185212351.csv";
  string testFileJSON = string(TEST_JSON_FILE);
  string outputFileJSON = string(TEST_ASSETS_DIR) + "test_output185212352.json";
  runStoreToMemory(memory, tokenizer.tokenize("abc = \"" + testFile + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("abcjson = \"" + testFileJSON + "\""));
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
  runStoreToMemory(memory, tokenizer.tokenize("ddd = \"" + outputFile + "\""));
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
  runStoreToMemory(memory, tokenizer.tokenize("dddjson = \"" + outputFileJSON + "\""));
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

void testSequelizeCommand() {
  cout << "- RUNNING: testSequelizeCommand" << endl;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  VariablesMemory memory;
  string testFile = string(TEST_CSV_1);
  runStoreToMemory(memory, tokenizer.tokenize("abc = \"" + testFile + "\""));
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
  testStoreToVariableCommand();
  testPrintCommand();
  testExportCommand();
  testSequelizeCommand();
}