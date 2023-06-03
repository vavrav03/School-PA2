#include "tokenizer.h"

using namespace std;

Tokenizer::Tokenizer(const std::vector<const std::string> specialCharacters) : specialCharacters(specialCharacters) {}

Tokenizer Tokenizer::createRelgebraInstance() {
  vector<const string> specialCharacters;
  specialCharacters.push_back("(");
  specialCharacters.push_back(")");
  specialCharacters.push_back("=");
  return Tokenizer(specialCharacters);
}

vector<Token> Tokenizer::tokenize(const string &command) {
  vector<Token> tokens;
  string buffer;
  bool in_quotes = false;

  for (const char &c: command) {
    if (c == '"') {
      in_quotes = !in_quotes;
      if (!in_quotes && !buffer.empty()) {
        tokens.push_back(Token(buffer, true));
        buffer.clear();
      }
    } else if (std::isspace(c) && !in_quotes) {
      if (!buffer.empty()) {
        tokens.push_back(Token(buffer, false));
        buffer.clear();
      }
    } else {
      buffer += c;
    }
  }

  if (!buffer.empty()) {
    tokens.push_back(Token(buffer, in_quotes));
  }

  return tokens;
}
