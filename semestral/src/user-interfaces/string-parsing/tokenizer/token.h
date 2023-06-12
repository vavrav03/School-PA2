#ifndef SEMESTRAL_TOKEN_H
#define SEMESTRAL_TOKEN_H

#include <string>
#include <iostream>

/**
 * Lexical token used by tokenizer (@see Tokenizer)
 */
class Token {

public:
  Token(const std::string &value, bool quoted) : value(value), quoted(quoted) {}

  friend std::ostream &operator<<(std::ostream &os, const Token &token) {
    if (token.quoted) {
      os << "\"" << token.value << "\"";
    } else {
      os << token.value;
    }
    return os;
  }

  const std::string value;
  const bool quoted;
};


#endif //SEMESTRAL_TOKEN_H
