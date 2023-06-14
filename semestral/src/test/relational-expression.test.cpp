#include "../user-interfaces/string-parsing/relational-expression/relational-expression-parser.h"
#include "../data-sources/expressions/expressions.h"
#include "test-list.h"
#include "../user-interfaces/console/commands/console-command.h"
#include <iostream>

using namespace std;

void assertReturnMatches(AbstractDataSource &expression, vector<vector<string> > &expected) {
  vector<int> equalCounters(expected.size(), 0);
  for (size_t i = 0; i < equalCounters.size(); i++) {
    vector<string> row = expression.getNextRow();
    for (size_t j = 0; j < expected.size(); j++) {
      if (equalsVectors(row, expected[j])) {
        equalCounters[j]++;
      }
    }
  }
  for (size_t i = 0; i < equalCounters.size(); i++) {
    assert(equalCounters[i] == 1);
  }
  assert(expression.getNextRow().empty());
}

void importTest1And2(VariablesMemory &memory) {
  string testFile1 = string(TEST_ASSETS_DIR) + "test-set1.csv";
  string testFile2 = string(TEST_ASSETS_DIR) + "test-set2.csv";
  ImportCommand command(memory);
  Tokenizer tokenizer = Tokenizer::getInstnace();
  command.run(tokenizer.tokenize("test1 = import \"" + testFile1 + "\""));
  command.run(tokenizer.tokenize("test2 = import \"" + testFile2 + "\""));
}

void testProjection() {
  cout << "RUNNING: testProjection" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  string testFile = string(TEST_ASSETS_DIR) + "test.csv";
  ImportCommand command(memory);
  command.run(tokenizer.tokenize("abc = import \"" + testFile + "\""));

  RelationalExpressionParser parser = RelationalExpressionParser::createDefaultInstance(memory);
  unique_ptr<AbstractDataSource>
      expression = parser.createExpressionFromTokens(tokenizer.tokenize("abc  [height   -  >vyska,    age]"));
  assert(toLowerCase(expression->toSQL()) == "select height as vyska, age from (select * from abc) as a");
  assert(expression->getHeaderSize() == 2);
  vector<string> rows = expression->getNextRow();
  assert(expression->getHeaderIndex("vyska") == 0);
  assert(expression->getHeaderIndex("age") == 1);
  assert(expression->getHeaderName(0) == "vyska");
  assert(expression->getHeaderName(1) == "age");
  assert(equalsVectors(rows, vector<string>{"180", "25"}));

  unique_ptr<AbstractDataSource> expression2 = parser.createExpressionFromTokens(
      tokenizer.tokenize("{{abc  [height   -  >vyska,    age]}}[vyska->height][height->opetvyska]"));
  assert(toLowerCase(expression2->toSQL()) ==
      toLowerCase(
          "SELECT height AS opetvyska FROM (SELECT vyska AS height FROM (SELECT height AS vyska, age FROM (select * from abc) AS a) AS b) AS c"));
  assert(expression2->getHeaderSize() == 1);
  rows = expression2->getNextRow();
  assert(expression2->getHeaderIndex("opetvyska") == 0);
  assert(expression2->getHeaderName(0) == "opetvyska");
  assert(rows[0] == "180");
}

void testIntersection() {
  cout << "RUNNING: testIntersection" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  importTest1And2(memory);

  RelationalExpressionParser parser = RelationalExpressionParser::createDefaultInstance(memory);
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 ∩    test2"));
  assert(toLowerCase(expression->toSQL())
             == toLowerCase("(select * from test1 INTERSECT select * from test2) AS a"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "height");
  vector<vector<string> > expected = {{"Alfred", "30", "175"},
                                      {"Betty", "20", "165"}};
  assertReturnMatches(*expression, expected);
}

void testUnion() {
  cout << "RUNNING: testUnion" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  importTest1And2(memory);

  RelationalExpressionParser parser = RelationalExpressionParser::createDefaultInstance(memory);
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1  ∪   test2"));
  assert(
      toLowerCase(expression->toSQL()) == toLowerCase("(select * from test1 UNION select * from test2) AS a"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "height");
  std::vector<std::vector<std::string> > data = {
      {"Mary", "28", "170"},
      {"John", "25", "180"},
      {"Alfred", "30", "175"},
      {"Betty", "20", "165"},
      {"Benjamin", "26", "80"},
      {"Octopus", "281", "1170"}
  };
  assertReturnMatches(*expression, data);
}

void testExcept() {
  cout << "RUNNING: testExcept" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  importTest1And2(memory);

  RelationalExpressionParser parser = RelationalExpressionParser::createDefaultInstance(memory);
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1  \\   test2"));
  assert(
      toLowerCase(expression->toSQL()) == toLowerCase("(select * from test1 EXCEPT select * from test2) AS a"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "height");
  std::vector<std::vector<std::string> > data = {
      {"Mary", "28", "170"},
      {"John", "25", "180"},
  };
  assertReturnMatches(*expression, data);
}

void testCartesian() {
  cout << "RUNNING: testCartesian" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  string testFile1 = string(TEST_ASSETS_DIR) + "test.json";
  string testFile2 = string(TEST_ASSETS_DIR) + "test-set1.csv";
  ImportCommand command(memory);
  command.run(tokenizer.tokenize("test1 = import \"" + testFile1 + "\""));
  command.run(tokenizer.tokenize("test2 = import \"" + testFile2 + "\""));

  RelationalExpressionParser parser = RelationalExpressionParser::createDefaultInstance(memory);
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 × test2"));
  assert(
      toLowerCase(expression->toSQL()) == toLowerCase("(select * from test1 CROSS JOIN select * from test2) AS a"));
  assert(expression->getHeaderSize() == 6);
  assert(expression->getHeaderName(0) == "a");
  assert(expression->getHeaderName(1) == "b");
  assert(expression->getHeaderName(2) == "c");
  assert(expression->getHeaderName(3) == "name");
  assert(expression->getHeaderName(4) == "age");
  assert(expression->getHeaderName(5) == "height");
  vector<vector<string> > expected = {
      {"1", "2", "3", "Mary", "28", "170"},
      {"1", "2", "3", "John", "25", "180"},
      {"1", "2", "3", "Alfred", "30", "175"},
      {"1", "2", "3", "Betty", "20", "165"},
      {"4", "5", "6", "Mary", "28", "170"},
      {"4", "5", "6", "John", "25", "180"},
      {"4", "5", "6", "Alfred", "30", "175"},
      {"4", "5", "6", "Betty", "20", "165"}
  };
  assertReturnMatches(*expression, expected);
}

void testExpression() {
  testProjection();
  testIntersection();
  testUnion();
  testExcept();
  testCartesian();
}
