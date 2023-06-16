#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING

#include "../../expression-evaluation/expression-evaluator.h"
#include "../../expression-evaluation/operation-part.h"
#include "./relational-operator-factories/relational-operator-factories.h"

template<typename T>
class ExpressionParser {
 public:
  ExpressionParser(std::vector<std::unique_ptr<OperationPartFactory<T>>> &&factories, VariablesMemory &memory) : memory(
      memory), factories(std::move(factories)), evaluator(memory) {

  }

  static ExpressionParser<AbstractDataSource> getInstance(VariablesMemory &memory) {
    std::vector<std::unique_ptr<OperationPartFactory<AbstractDataSource> >> factories;
    factories.push_back(std::make_unique<LeftBracketRelationOperandFactory>());
    factories.push_back(std::make_unique<RightBracketRelationOperandFactory>());
    factories.push_back(std::make_unique<ProjectionOperatorFactory>());
    factories.push_back(std::make_unique<IntersectionOperatorFactory>());
    factories.push_back(std::make_unique<UnionOperatorFactory>());
    factories.push_back(std::make_unique<ExceptOperatorFactory>());
    factories.push_back(std::make_unique<CartesianProductOperatorFactory>());
    factories.push_back(std::make_unique<NaturalJoinOperatorFactory>());
    factories.push_back(std::make_unique<CSVOperandFactory>(memory));
    factories.push_back(std::make_unique<JSONOperandFactory>(memory));
    factories.push_back(std::make_unique<VariableOperandFactory>(memory));
    return ExpressionParser(std::move(factories), memory);
  }

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
  createInfixFromTokens(const std::vector<Token> &tokens) const {
    size_t nextTokenIndex = 0;
    std::vector<std::unique_ptr<OperationPart<AbstractDataSource> >> infix;
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
  VariablesMemory &memory;
  std::vector<std::unique_ptr<OperationPartFactory<T>>> factories;
  ExpressionEvaluator<T> evaluator;
};

#endif //SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING
