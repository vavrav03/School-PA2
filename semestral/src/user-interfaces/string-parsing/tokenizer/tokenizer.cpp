#include "tokenizer.h"

using namespace std;

Tokenizer::Tokenizer(const std::vector<std::string> &specialCharacters) : specialCharacters(specialCharacters) {}

Tokenizer Tokenizer::getInstnace() {
  // not all operations have to be here, but it makes sense to have them repeated despite being mentioned elsewhere
  return Tokenizer({"∪", "∩", "\\", "×", "÷",
                    "*", "!",
                    "⊆", "⊂", "=",
                    "{", "}", ",", "(", ")", "[", "]", "-",
                    "∧", "∨", "¬", "⇒", "⇔", "⊼", "⊽",
                    "=", "<", ">", "~"});
}

vector<Token> Tokenizer::tokenize(const string &command) {
  vector<Token> tokens;
  string buffer;
  bool in_quotes = false;

  for (const char &c : command) {
    if (c == '"') {
      in_quotes = !in_quotes;
      if (!buffer.empty()) {
        tokens.push_back(Token(buffer, !in_quotes));
        buffer.clear();
      }
    } else if (std::isspace(c) && !in_quotes) {
      if (!buffer.empty()) {
        tokens.push_back(Token(buffer, false));
        buffer.clear();
      }
    } else if (!in_quotes &&
        isSpecialCharacter(string(1, c))) {
      if (!buffer.empty()) {
        tokens.push_back(Token(buffer, false));
        buffer.clear();
      }
      tokens.push_back(Token(string(1, c), false));
    } else {
      buffer += c;
    }
  }

  if (!buffer.empty()) {
    tokens.push_back(Token(buffer, in_quotes));
  }

  return tokens;
}

bool Tokenizer::isSpecialCharacter(const std::string &character) const {
  for (const string &specialCharacter : specialCharacters) {
    if (specialCharacter == character) {
      return true;
    }
  }
  return false;
}
