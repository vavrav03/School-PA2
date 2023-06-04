#ifndef SEMESTRAL_TOKENIZER_H
#define SEMESTRAL_TOKENIZER_H

#include <vector>
#include <string>
#include "./token.h"

/**
 * Tokenizer is used to split string command into tokens.
 */
class Tokenizer {

public:
  Tokenizer(const std::vector<const std::string> specialCharacters);

  std::vector<Token> tokenize(const std::string &command);

  /**
   * Tokenizer with default special characters used in relational algebra
   * @return
   */
  static Tokenizer createRelgebraInstance();
public:
  /**
   * If these characters are found in a non-quoted part, they are assumed to be separate tokens
   */
  const std::vector<const std::string> specialCharacters;
};


#endif //SEMESTRAL_TOKENIZER_H
