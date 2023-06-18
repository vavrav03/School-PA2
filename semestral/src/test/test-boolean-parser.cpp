#include "./test.h"
#include "../user-interfaces/string-parsing/expression-parser.h"

using namespace std;

void testBooleanParser() {
  Tokenizer tokenizer = Tokenizer::getInstnace();
  std::vector<std::string> row = {"95", "bbb", "95"};
  std::unordered_map<std::string, size_t> indexMap = {{"a", 0}, {"b", 1}, {"c", 2}};
  HeaderRowMapping mapping(row, indexMap);
  auto parser = ExpressionParser<AbstractBooleanExpression>::getInstance();
  assert(parser.createExpressionFromTokens(tokenizer.tokenize("a =c"))->evaluate(mapping));
  assert(!parser.createExpressionFromTokens(tokenizer.tokenize("a=b"))->evaluate(mapping));
  assert(parser.createExpressionFromTokens(tokenizer.tokenize("a=b ∨ a=c"))->evaluate(mapping));
  assert(!parser.createExpressionFromTokens(tokenizer.tokenize("a=b ∧ a=c"))->evaluate(mapping));
  assert(parser.createExpressionFromTokens(tokenizer.tokenize("(a=b)'''"))->evaluate(mapping));
  assert(parser.createExpressionFromTokens(tokenizer.tokenize("(a=a ⇔ a=c) ∧ (a=a ⊕ a=b)"))->evaluate(mapping));
  assert(parser.createExpressionFromTokens(tokenizer.tokenize("(a=a ⇒ a=c) ∨ (a=a ⊕ a=a)'"))->evaluate(mapping));
  assert(!parser.createExpressionFromTokens(tokenizer.tokenize("(a=a ↓ a=c) ∨ (a=a ↑ a=c)"))->evaluate(mapping));
  assert(parser.createExpressionFromTokens(tokenizer.tokenize("(a >= 90) ∧ (a <= 99)"))->evaluate(mapping));

  assert(parser.createExpressionFromTokens(tokenizer.tokenize("a=b ∨ a=c"))->toSQL() == "(a = b) OR (a = c)");
}