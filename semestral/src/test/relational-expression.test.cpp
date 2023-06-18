#include "../expression-evaluation/expression-evaluator.h"
#include "test.h"
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
        break;
      }
    }
  }
  for(size_t i = 0; i < equalCounters.size(); i++) {
    for(size_t j = i + 1; j < equalCounters.size(); j++) {
      if(equalsVectors(expected[i], expected[j])) { // non-distinct pile up in the first one
        equalCounters[i]--;
        equalCounters[j]++;
      }
    }
  }
  for (size_t i = 0; i < equalCounters.size(); i++) {
    assert(equalCounters[i] == 1);
  }
  assert(expression.getNextRow().empty());
}

void testProjection() {
  cout << "RUNNING: testProjection" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  runStoreToMemory(memory, tokenizer.tokenize("abc = \"" + string(TEST_CSV_1) + "\""));

  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource>
      expression = parser.createExpressionFromTokens(tokenizer.tokenize("abc  [height   -  >vyska,    age]"));
  assert(toLowerCase(expression->toSQL()) == "select height as vyska, age from (select * from test)");
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
          "SELECT height AS opetvyska FROM (SELECT vyska AS height FROM (SELECT height AS vyska, age FROM (select * from test)))"));
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
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_SET_1) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_2) + "\""));

  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 ∩    test2"));
  assert(toLowerCase(expression->toSQL())
             == toLowerCase("SELECT * FROM (select * from test-set1 INTERSECT select * from test-set2)"));
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
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_SET_1) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_2) + "\""));

  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1  ∪   test2"));
  assert(
      toLowerCase(expression->toSQL())
          == toLowerCase("SELECT * FROM (select * from test-set1 UNION select * from test-set2)"));
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
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_SET_1) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_2) + "\""));

  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1  \\   test2"));
  assert(
      toLowerCase(expression->toSQL())
          == toLowerCase("SELECT * FROM (select * from test-set1 EXCEPT select * from test-set2)"));
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
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_JSON_FILE) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_1) + "\""));

  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 × test2"));
  assert(
      toLowerCase(expression->toSQL())
          == toLowerCase("SELECT * FROM (select * from test CROSS JOIN select * from test-set1)"));
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
      {"4", "5", "6", "Betty", "20", "165"},
  };
  assertReturnMatches(*expression, expected);

  try {
    parser.createExpressionFromTokens(tokenizer.tokenize("test1 × test1"));
    assert(false); // must rename columns
  } catch (...) {}
  expression = parser.createExpressionFromTokens(tokenizer.tokenize("test1[a->xyz] × test1"));
  assert(expression->getHeaderSize() == 4);
  assert(expression->getHeaderName(0) == "xyz");
  assert(expression->getHeaderName(1) == "a");
  assert(expression->getHeaderName(2) == "b");
  assert(expression->getHeaderName(3) == "c");
  expected = {
      {"1", "1", "2", "3"},
      {"1", "4", "5", "6"},
      {"4", "1", "2", "3"},
      {"4", "4", "5", "6"}
  };
  assertReturnMatches(*expression, expected);
}

void testNaturalJoin() {
  cout << "RUNNING: natural join" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_JOIN_1) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_1) + "\""));
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 * test2"));
  assert(expression->getHeaderSize() == 4);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "school");
  assert(expression->getHeaderName(3) == "height");
  vector<vector<string> > expected = {
      {"Mary", "28", "MIT", "170"},
      {"Mary", "28", "Princeton", "170"},
      {"Betty", "20", "CUNI", "165"}
  };
  assertReturnMatches(*expression, expected);
}

void testNaturalSemiJoins() {
  cout << "RUNNING: left natural semi join" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_JOIN_1) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_1) + "\""));
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 <* test2"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "school");
  vector<vector<string> > expected = {
      {"Mary", "28", "MIT"},
      {"Mary", "28", "Princeton"},
      {"Betty", "20", "CUNI"}
  };
  assertReturnMatches(*expression, expected);

  cout << "RUNNING: right natural semi join" << endl;

  expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 *> test2"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "height");
  expected = {
      {"Mary", "28", "170"},
      {"Mary", "28", "170"},
      {"Betty", "20", "165"}
  };
}

void testNaturalAntiJoins() {
  cout << "RUNNING: left natural anti join" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_JOIN_1) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_1) + "\""));
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 !<* test2"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "school");
  vector<vector<string> > expected = {
      {"Mary", "17", "Harvard"},
      {"Alfred", "29", "CTU"}
  };
  assertReturnMatches(*expression, expected);

  cout << "RUNNING: right natural semi join" << endl;

  expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1 !*> test2"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "height");
  expected = {
      {"John", "25", "180"},
      {"Alfred", "30", "175"}
  };
  assertReturnMatches(*expression, expected);
}

void testSelection() {
  cout << "RUNNING: selection" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_SET_1) + "\""));
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("test1(name = Mary ∨ age >= 28)"));
  assert(expression->getHeaderSize() == 3);
  assert(expression->getHeaderName(0) == "name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "height");
  vector<vector<string> > expected = {
      {"Mary", "28", "170"},
      {"Alfred", "30", "175"}
  };
  assertReturnMatches(*expression, expected);
}

void testThetaJoin() {
  cout << "RUNNING: theta join" << endl;
  VariablesMemory memory;
  Tokenizer tokenizer = Tokenizer::getInstnace();
  runStoreToMemory(memory, tokenizer.tokenize("test1 = \"" + string(TEST_CSV_JOIN_1) + "\""));
  runStoreToMemory(memory, tokenizer.tokenize("test2 = \"" + string(TEST_CSV_SET_1) + "\""));
  auto parser(ExpressionParser<AbstractDataSource>::getInstance(memory));
  unique_ptr<AbstractDataSource> expression = parser.createExpressionFromTokens(
      tokenizer.tokenize("{test1[name->a_name, age]}[a_name=b_name]{test2[name->b_name, height]}"));
  assert(expression->getHeaderSize() == 4);
  assert(expression->getHeaderName(0) == "a_name");
  assert(expression->getHeaderName(1) == "age");
  assert(expression->getHeaderName(2) == "b_name");
  assert(expression->getHeaderName(3) == "height");
  vector<vector<string> > expected = {
      {"Mary", "17", "Mary", "170"},
      {"Mary", "28", "Mary", "170"},
      {"Mary", "28", "Mary", "170"},
      {"Alfred", "29", "Alfred", "175"},
      {"Betty", "20", "Betty", "165"}
  };
  assertReturnMatches(*expression, expected);
}

void testExpression() {
  testProjection();
  testIntersection();
  testUnion();
  testExcept();
  testCartesian();
  testNaturalJoin();
  testNaturalSemiJoins();
  testNaturalAntiJoins();
  testSelection();
  testThetaJoin();
}
