#include "./test.h"
#include "../user-interfaces/string-parsing/expression-parser.h"

using namespace std;

void testBooleanParser() {
  Tokenizer tokenizer = Tokenizer::getInstnace();
  std::unordered_map<std::string, size_t> indexMap = {{"a", 0}, {"b", 1}, {"c", 2}};
  std::vector<std::string> row = {"95", "bbb", "95"};
  auto parser = ExpressionParser<bool>::getInstance(indexMap, row);
  try {
    parser.createExpressionFromTokens(tokenizer.tokenize("a=d"));
    assert(false);
  } catch (...) {
    assert(true);
  }
  assert(*parser.createExpressionFromTokens(tokenizer.tokenize("a=c")));
  assert(!*parser.createExpressionFromTokens(tokenizer.tokenize("a=b")));
  assert(*parser.createExpressionFromTokens(tokenizer.tokenize("a=b ∨ a=c")));
  assert(!*parser.createExpressionFromTokens(tokenizer.tokenize("a=b ∧ a=c")));
  assert(*parser.createExpressionFromTokens(tokenizer.tokenize("(a=b)'''")));
  assert(*parser.createExpressionFromTokens(tokenizer.tokenize("(a=a ⇔ a=c) ∧ (a=a ⊕ a=b)")));
  assert(*parser.createExpressionFromTokens(tokenizer.tokenize("(a=a ⇒ a=c) ∨ (a=a ⊕ a=a)'")));
  assert(!*parser.createExpressionFromTokens(tokenizer.tokenize("(a=a ↓ a=c) ∨ (a=a ↑ a=c)")));
}