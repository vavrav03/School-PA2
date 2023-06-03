#ifndef SEMESTRAL_TOKENIZER_H
#define SEMESTRAL_TOKENIZER_H

#include <vector>
#include <string>
#include "./token.h"

class Tokenizer {

public:
  Tokenizer(const std::vector<const std::string> specialCharacters);
  std::vector<Token> tokenize(const std::string &command);
  static Tokenizer createRelgebraInstance();
public:
  const std::vector<const std::string> specialCharacters;
};


#endif //SEMESTRAL_TOKENIZER_H
