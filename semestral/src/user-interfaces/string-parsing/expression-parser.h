#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING

#include "../../expression-evaluation/expression-evaluator.h"
#include "../../expression-evaluation/operation-part.h"
#include "../../boolean-expressions/boolean-expressions.h"
#include "./operator-factories/operation-factory.h"

template<typename T>
class ExpressionParser {
 public:
  ExpressionParser(std::vector<std::unique_ptr<OperationPartFactory<T>>> &&factories)
      : factories(std::move(factories)), evaluator() {
  }

  /**
   * Creates instance for creation of evaluatable relational expression
   * @param memory
   * @return
   */
  static ExpressionParser<AbstractDataSource> getInstance(VariablesMemory &memory);

  /**
   * Creates instance for creation of evaluatable boolean expression
   * @return
   */
  static ExpressionParser<AbstractBooleanExpression> getInstance();

  /**
   *
   * @param tokens
   * @return Evaluateable expression in T format
   */
  std::unique_ptr<T> createExpressionFromTokens(const std::vector<Token> &tokens) const {
    return evaluator.createExpressionFromPostfix(evaluator.createPostfixFromInfix(createInfixFromTokens(tokens)));
  }
 private:
  std::vector<std::unique_ptr<OperationPart<T>>>

  /**
   * Convert Token vector format to logical infix format using factories of the class
   * @param tokens
   * @return
   */
  createInfixFromTokens(const std::vector<Token> &tokens) const {
    size_t nextTokenIndex = 0;
    std::vector<std::unique_ptr<OperationPart<T> >> infix;
    while (nextTokenIndex < tokens.size()) {
      bool found = false;
      for (auto &factory : factories) {
        if (factory->canCreate(tokens, nextTokenIndex)) {
          infix.push_back(factory->create(tokens, nextTokenIndex));
          found = true;
          break;
        }
      }
      if (!found) {
        throw std::runtime_error("Unknown token " + tokens[nextTokenIndex].value);
      }
    }
    return infix;
  }
  std::vector<std::unique_ptr<OperationPartFactory<T>>> factories;
  ExpressionEvaluator<T> evaluator;
};

#endif //SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING
