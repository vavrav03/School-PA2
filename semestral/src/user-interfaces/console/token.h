#ifndef SEMESTRAL_TOKEN_H
#define SEMESTRAL_TOKEN_H

#include <string>

class Token {

public:
  Token(const std::string &value, bool quoted) : value(value), quoted(quoted) {}

  const std::string value;
  const bool quoted;
};


#endif //SEMESTRAL_TOKEN_H
