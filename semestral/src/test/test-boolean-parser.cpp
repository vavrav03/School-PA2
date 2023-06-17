#include "./test.h"
#include "../user-interfaces/string-parsing/expression-parser.h"

using namespace std;

void testBooleanParser(){
  Tokenizer tokenizer = Tokenizer::getInstnace();
  auto parser = ExpressionParser<bool>::getInstance();
  auto result = parser.createExpressionFromTokens(tokenizer.tokenize("a=a ∧ a=a ∧ aaaaa=aaaaa"));
  cout << *result;
}