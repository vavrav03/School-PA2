#ifndef SEMESTRAL_TOKEN_H
#define SEMESTRAL_TOKEN_H

#include <string>

/**
 * Lexical token used by tokenizer (@see Tokenizer)
 */
class Token {

public:
  Token(const std::string &value, bool quoted) : value(value), quoted(quoted) {}

  const std::string value;
  const bool quoted;
};


#endif //SEMESTRAL_TOKEN_H
