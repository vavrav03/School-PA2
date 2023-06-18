#include "tokenizer.h"

using namespace std;

Tokenizer::Tokenizer(const std::vector<std::string> &specialCharacters) : specialCharacters(specialCharacters) {}

Tokenizer Tokenizer::getInstnace() {
  // not all operations have to be here, but it makes sense to have them repeated despite being mentioned elsewhere
  return Tokenizer({"∪", "∩", "\\", "×", "÷",
                    "*", "!",
                    "⊆", "⊂", "=",
                    "{", "}", ",", "(", ")", "[", "]", "-",
                    "∧", "∨", "'", "⇒", "⇔", "↓", "↑",
                    "=", "<", ">"});
}

vector<Token> Tokenizer::tokenize(const string &command) {
  vector<Token> tokens;
  string buffer;
  bool inQuotes = false;

  for (const char &c : command) {
    if (c == '"') {
      inQuotes = !inQuotes;
      if (!buffer.empty()) {
        tokens.push_back(Token(buffer, !inQuotes));
        buffer.clear();
      }
    } else if (std::isspace(c) && !inQuotes) {
      if (!buffer.empty()) {
        tokens.push_back(Token(buffer, false));
        buffer.clear();
      }
    } else if (!inQuotes &&
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
    tokens.push_back(Token(buffer, inQuotes));
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
