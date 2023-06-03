#include "./console-command.h"
#include "../tokenizer/tokenizer.h"

using namespace std;

void testImportCommand(Tokenizer &tokenizer, VariablesMemory &memory) {
  ImportCommand command(memory);
  const string correct1 = "abc = import \"../../../../src/test/assets/test.csv\"";
  const string correct2 = "ddd=import\"../../../../src/test/assets/test.csv\"";
  const string incorrectAlreadyExistingVariable = "abc = import \"../../../../src/test/assets/test.csv\" select * from abc";
  const string incorrectUnquoted = "abc = import ../../../../src/test/assets/test.csv";
  const string incorrectWithoutImport = "abc = \"../../../../src/test/assets/test.csv\"";
  const string incorrectFollowedByCommand = "abc = import \"../../../../src/test/assets/test.csv\" select * from abc";
//  command.run(tokenizer.tokenize(correct1));
//  command.run(tokenizer.tokenize(correct2));
//  try {
//    command.run(tokenizer.tokenize(incorrectAlreadyExistingVariable));
//    assert(false);
//  } catch (exception &e) {
//    assert(true);
//  }

//  assert(memory.getVariable("abc")->getRelation()->getRowsCount() == 3);

  assert(command.shouldRun(tokenizer.tokenize(correct1)));
  assert(command.shouldRun(tokenizer.tokenize(correct2)));
  assert(!command.shouldRun(tokenizer.tokenize(incorrectUnquoted)));
  assert(!command.shouldRun(tokenizer.tokenize(incorrectWithoutImport)));
  assert(!command.shouldRun(tokenizer.tokenize(incorrectFollowedByCommand)));
}

void testConsoleCommands() {
  Tokenizer tokenizer = Tokenizer::createRelgebraInstance();
  VariablesMemory memory;
  testImportCommand(tokenizer, memory);
}