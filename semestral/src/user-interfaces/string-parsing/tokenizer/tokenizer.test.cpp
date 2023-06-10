#include "./tokenizer.h"
#include <iostream>

using namespace std;

void testTokenizeMethod() {
  cout << "- RUNNING: testTokenizeMethod" << endl;
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

  tokens = tokenizer.tokenize("abc=import \"format.csv\"");
  assert(tokens[0].value == "abc");
  assert(tokens[1].value == "=");
  assert(tokens[2].value == "import");
  assert(tokens[3].value == "format.csv");

  tokens = tokenizer.tokenize("abc= import\"format.csv\"");
  assert(tokens[0].value == "abc");
  assert(tokens[1].value == "=");
  assert(tokens[2].value == "import");
  assert(tokens[3].value == "format.csv");

  tokens = tokenizer.tokenize("abc={    a   ∩   b(\"a===b\" = 1   ∨ (x = 2))}[b,  a]");
  assert(tokens[0].value == "abc");
  assert(tokens[1].value == "=");
  assert(tokens[2].value == "{");
  assert(tokens[3].value == "a");
  assert(tokens[4].value == "∩");
  assert(tokens[5].value == "b");
  assert(tokens[6].value == "(");
  assert(tokens[7].value == "a===b");
  assert(tokens[7].quoted);
  assert(tokens[8].value == "=");
  assert(tokens[9].value == "1");
  assert(tokens[10].value == "∨");
  assert(tokens[11].value == "(");
  assert(tokens[12].value == "x");
  assert(tokens[13].value == "=");
  assert(tokens[14].value == "2");
  assert(tokens[15].value == ")");
  assert(tokens[16].value == ")");
  assert(tokens[17].value == "}");
  assert(tokens[18].value == "[");
  assert(tokens[19].value == "b");
  assert(tokens[20].value == ",");
  assert(tokens[21].value == "a");
  assert(tokens[22].value == "]");
}
