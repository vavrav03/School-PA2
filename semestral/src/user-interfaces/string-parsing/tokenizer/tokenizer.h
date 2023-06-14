#ifndef SEMESTRAL_TOKENIZER_H
#define SEMESTRAL_TOKENIZER_H

#include <vector>
#include <string>
#include "./token.h"

/**
 * Tokenizer removes or does similar operations on unformatted strings so that additional characters without any
 * additional meaning do not effect the end result of a query - added spaces, new lines, tabs are removed. It also
 * splits the string into tokens that are separated by special characters.
 * cause syntax errors - e.g. extra spaces.
 */
class Tokenizer {

 public:
  Tokenizer(const std::vector<std::string> &specialCharacters);

  std::vector<Token> tokenize(const std::string &command);

  /**
   * Tokenizer with default special characters used in relational algebra
   * @return
   */
  static Tokenizer getInstnace();

  /**
   * If these characters are found in a non-quoted part, they are assumed to be separate tokens
   */
  bool isSpecialCharacter(const std::string &character) const;
 private:
  const std::vector<std::string> specialCharacters;
};

#endif //SEMESTRAL_TOKENIZER_H
