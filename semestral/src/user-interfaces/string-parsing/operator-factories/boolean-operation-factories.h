#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_OPERATOR_FACTORIES_BOOLEAN_OPERATION_FACTORIES_H_
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_OPERATOR_FACTORIES_BOOLEAN_OPERATION_FACTORIES_H_

#include "./operation-factory.h"
#include "../tokenizer/token.h"
#include "../../../expression-evaluation/operation-part.h"
#include "../../../expression-evaluation/boolean-operation-part.h"
#include "../../../boolean-expressions/boolean-expressions.h"

template<typename ConcreteOperand>
class BooleanOperandFactory : public OperationPartFactory<AbstractBooleanExpression> {
 public:
  BooleanOperandFactory(const std::vector<std::string> &operators)
      : operatorParts({operators}) {}
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    if (nextTokenIndex + 2 + operatorParts.size() > tokens.size()) {
      return false;
    }
    for (size_t i = 0; i < operatorParts.size(); i++) {
      if (tokens[nextTokenIndex + i + 1].value != operatorParts[i]) {
        return false;
      }
    }
    return true;
  }
  std::unique_ptr<OperationPart<AbstractBooleanExpression> > create(const std::vector<Token> &tokens,
                                               size_t &nextTokenIndex) const override {
    auto leftName = tokens[nextTokenIndex].value;
    auto rightName = tokens[nextTokenIndex + operatorParts.size() + 1].value;
    nextTokenIndex += operatorParts.size() + 2;
    return std::make_unique<ConcreteOperand>(leftName, rightName);
  }
 private:
  std::vector<std::string> operatorParts;
};

#endif //SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_OPERATOR_FACTORIES_BOOLEAN_OPERATION_FACTORIES_H_
