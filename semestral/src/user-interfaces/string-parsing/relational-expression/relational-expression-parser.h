#ifndef SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
#define SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H

#include "../operation-part.h"
#include "expression-operation-part.h"
#include "../../abstract/variables-memory.h"
#include <vector>

class RelationalExpressionParser {
 public:
  RelationalExpressionParser(std::vector<std::unique_ptr<OperationPartFactory>> &factories, VariablesMemory &memory);
  static RelationalExpressionParser createDefaultInstance(const Tokenizer &tokenizer, VariablesMemory &memory);
  std::unique_ptr<AbstractDataSource> createExpressionFromTokens(const std::vector<Token> &tokens) const;
 private:
  std::vector<std::unique_ptr<OperationPart>> createInfixFromTokens(const std::vector<Token> &tokens) const;
  std::unique_ptr<AbstractDataSource>
  createExpressionFromPostfix(const std::vector<std::unique_ptr<OperationPart>> &parts) const;
  std::vector<std::unique_ptr<OperationPartFactory>> factories;
  VariablesMemory &memory;
};

#endif //SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
