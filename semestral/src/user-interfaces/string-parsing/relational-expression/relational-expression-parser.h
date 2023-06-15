#ifndef SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
#define SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H

#include "../operation-part.h"
#include "expression-operation-part.h"
#include "../../abstract/variables-memory.h"
#include <vector>

class RelationalExpressionParser {
 public:
  RelationalExpressionParser(std::vector<std::unique_ptr<OperationPartFactory<AbstractDataSource>>> &factories,
                             VariablesMemory &memory);
  static RelationalExpressionParser createDefaultInstance(VariablesMemory &memory);
  std::unique_ptr<AbstractDataSource> createExpressionFromTokens(const std::vector<Token> &tokens) const;
 private:
  std::vector<std::unique_ptr<OperationPart<AbstractDataSource>>> createInfixFromTokens(const std::vector<Token> &tokens) const;
  std::unique_ptr<AbstractDataSource>
  createExpressionFromPostfix(const std::vector<std::unique_ptr<OperationPart<AbstractDataSource>>> &parts) const;
  std::vector<std::unique_ptr<OperationPartFactory<AbstractDataSource>>> factories;
  VariablesMemory &memory;
};

#endif //SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
