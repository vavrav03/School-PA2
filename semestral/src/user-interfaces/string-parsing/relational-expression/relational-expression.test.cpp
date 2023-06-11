#include "relational-expression-parser.h"
#include "../../../data-sources/expressions/expressions.h"
#include "../../../../src/test/test_list.h"
#include "../../console/commands/console-command.h"
#include <iostream>

using namespace std;

void testProjection(Tokenizer &tokenizer) {
  VariablesMemory memory;
  string testFile = string(TEST_ASSETS_DIR) + "test.csv";
  ImportCommand command(memory);
  command.run(tokenizer.tokenize("abc = import \"" + testFile + "\""));

  RelationalExpressionParser parser = RelationalExpressionParser::createDefaultInstance(tokenizer, memory);
  shared_ptr<AbstractExpression> expression = parser.createExpressionFromTokens(
          tokenizer.tokenize("abc  [height   -  >vyska,    age]"));
  assert(toLowerCase(expression->toSQL()) == "select height as vyska, age from (select * from abc) as a");
  assert(expression->getHeaderSize() == 2);
  assert(expression->hasNextRow());
  vector<string> rows = expression->getNextRow();
  assert(expression->getHeaderIndex("vyska") == 0);
  assert(expression->getHeaderIndex("age") == 1);
  assert(expression->getHeaderName(0) == "vyska");
  assert(expression->getHeaderName(1) == "age");
  assert(rows[0] == "180");
  assert(rows[1] == "25");
  assert(!expression->hasNextRow());

  shared_ptr<AbstractExpression> expression2 = parser.createExpressionFromTokens(
          tokenizer.tokenize("{{abc  [height   -  >vyska,    age]}}[vyska->height][height->opetvyska]"));
  assert(toLowerCase(expression2->toSQL()) ==
         toLowerCase(
                 "SELECT height AS opetvyska FROM (SELECT vyska AS height FROM (SELECT height AS vyska, age FROM (select * from abc) AS a) AS b) AS c"));
  assert(expression2->getHeaderSize() == 1);
  rows = expression2->getNextRow();
  assert(expression2->getHeaderIndex("opetvyska") == 0);
  assert(expression2->getHeaderName(0) == "opetvyska");
  assert(rows[0] == "180");
  assert(!expression2->hasNextRow());
}

void testExpression() {
  Tokenizer tokenizer = Tokenizer::createRelgebraInstance();
  testProjection(tokenizer);
}
