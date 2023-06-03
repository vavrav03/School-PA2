#include "./tokenizer.h"

using namespace std;

void testTokenizeMethod() {
  Tokenizer tokenizer = Tokenizer::createRelgebraInstance();
  std::vector<Token> tokens = tokenizer.tokenize("     help     anotherH elp    ");
  assert(tokens[0].value == "help");
  assert(tokens[1].value == "anotherH");
  assert(tokens[2].value == "elp");
  assert(!tokens[0].quoted);
  assert(!tokens[1].quoted);
  assert(!tokens[2].quoted);

  tokens = tokenizer.tokenize("     \"help\"     \"anotherH elp   \" ");
  assert(tokens[0].value == "help");
  assert(tokens[1].value == "anotherH elp   ");
  assert(tokens[0].quoted);
  assert(tokens[1].quoted);

  tokens = tokenizer.tokenize(" abc = import \"format.csv\"");
  assert(tokens[0].value == "abc");
  assert(tokens[1].value == "=");
  assert(tokens[2].value == "import");
  assert(tokens[3].value == "format.csv");
  assert(!tokens[0].quoted);
  assert(!tokens[1].quoted);
  assert(!tokens[2].quoted);
  assert(tokens[3].quoted);
}
