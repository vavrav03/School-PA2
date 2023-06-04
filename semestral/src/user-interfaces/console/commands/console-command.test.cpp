#include "./console-command.h"
#include "../tokenizer/tokenizer.h"

#include "../../../../src/test/test_list.h"

using namespace std;

void testImportCommand(Tokenizer &tokenizer) {
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
  assert(memory.get("abc")->getHeader()[0] == "name");
  assert(memory.get("abc")->getHeader()[1] == "age");
  assert(memory.get("abc")->getHeader()[2] == "height");
  vector<string> row = memory.get("abc")->getNextRow();
  assert(row[0] == "John");
  assert(row[1] == "25");
  assert(row[2] == "180");

  assert(command.matchesSyntactically(tokenizer.tokenize(correct2)));
  command.run(tokenizer.tokenize(correct2));
  assert(memory.get("ddd")->getHeader()[0] == "name");
  assert(memory.get("ddd")->getHeader()[1] == "age");
  assert(memory.get("ddd")->getHeader()[2] == "height");
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

void testConsoleCommands() {
  Tokenizer tokenizer = Tokenizer::createRelgebraInstance();
  testImportCommand(tokenizer);
  testPrintCommand(tokenizer);
}