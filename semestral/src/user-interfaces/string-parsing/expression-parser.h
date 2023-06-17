#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING

#include "../../expression-evaluation/expression-evaluator.h"
#include "../../expression-evaluation/operation-part.h"
#include "./operator-factories/relational-operation-factories.h"
#include "./operator-factories/boolean-operation-factories.h"
#include "../../expression-evaluation/boolean-operation-part.h"

template<typename T>
class ExpressionParser {
 public:
  ExpressionParser(std::vector<std::unique_ptr<OperationPartFactory<T>>> &&factories)
      : factories(std::move(factories)), evaluator() {
  }

  static ExpressionParser<AbstractDataSource> getInstance(VariablesMemory &memory) {
    std::vector<std::unique_ptr<OperationPartFactory<AbstractDataSource> >> factories;
    // the ones with more characters must be first to avoid matching the shorter ones
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, LeftNaturalAntiJoin>>(
        std::vector<std::string>{"!", "<", "*"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, RightNaturalAntiJoin>>(
        std::vector<std::string>{"!", "*", ">"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, LeftNaturalSemiJoinOperator>>(
        std::vector<std::string>{"<", "*"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, RightNaturalSemiJoinOperator>>(
        std::vector<std::string>{"*", ">"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource,
                                                                  LeftBracketOperand<AbstractDataSource>>>(
        std::vector<std::string>{"{"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource,
                                                                  RightBracketOperand<AbstractDataSource>>>(
        std::vector<std::string>{"}"}));
    factories.push_back(std::make_unique<ProjectionOperatorFactory>());
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, IntersectionOperator>>(
        std::vector<std::string>{"∩"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, UnionOperator>>(
        std::vector<std::string>{"∪"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, ExceptOperator>>(
        std::vector<std::string>{"\\"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, CartesianProductOperator>>(
        std::vector<std::string>{"×"}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<AbstractDataSource, NaturalJoinOperator>>(
        std::vector<std::string>{"*"}));
    factories.push_back(std::make_unique<CSVOperandFactory>());
    factories.push_back(std::make_unique<JSONOperandFactory>());
    factories.push_back(std::make_unique<VariableOperandFactory>(memory));
    return ExpressionParser(std::move(factories));
  }

  static ExpressionParser<bool> getInstance() {
    std::vector<std::unique_ptr<OperationPartFactory<bool>>> factories;
    factories.push_back(std::make_unique<CharacterOperatorFactory<bool, LeftBracketOperand<bool>>>(
        std::vector<std::string>{"("}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<bool, RightBracketOperand<bool>>>(
        std::vector<std::string>{")"}));
    factories.push_back(std::make_unique<BooleanOperandFactory<EqualityOperand>>(std::vector<std::string>{"="}));
    factories.push_back(std::make_unique<CharacterOperatorFactory<bool, AndOperator>>(
        std::vector<std::string>{"∧"}));
    return ExpressionParser(std::move(factories));
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
