#ifndef SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
#define SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H

#include <vector>
#include "./relational-expression/expression-operation-part.h"
#include "./operation-part.h"
#include "../abstract/variables-memory.h"

template<typename T>
class ExpressionParser {
 public:
  ExpressionParser(std::vector<std::unique_ptr<OperationPartFactory<T>>> &&factories,
                   VariablesMemory &memory) : memory(memory), factories(std::move(factories)) {}

  static ExpressionParser<AbstractDataSource> getInstance(VariablesMemory &memory) {
    std::vector<std::unique_ptr<OperationPartFactory<AbstractDataSource> >> factories;
    factories.push_back(std::make_unique<LeftBracketRelationOperandFactory>());
    factories.push_back(std::make_unique<RightBracketRelationOperandFactory>());
    factories.push_back(std::make_unique<ProjectionOperatorFactory>());
    factories.push_back(std::make_unique<IntersectionOperatorFactory>());
    factories.push_back(std::make_unique<UnionOperatorFactory>());
    factories.push_back(std::make_unique<ExceptOperatorFactory>());
    factories.push_back(std::make_unique<CartesianProductOperatorFactory>());
    factories.push_back(std::make_unique<CSVOperandFactory>());
    factories.push_back(std::make_unique<JSONOperandFactory>());
    factories.push_back(std::make_unique<VariableOperandFactory>(memory));
    return ExpressionParser(std::move(factories), memory);
  }

  /**
   *
   * @param tokens
   * @return Evaluateable expression in T format
   */
  std::unique_ptr<T> createExpressionFromTokens(const std::vector<Token> &tokens) const {
    return createExpressionFromPostfix(createPostfixFromInfix(createInfixFromTokens(tokens)));
  }
 private:
  std::vector<std::unique_ptr<OperationPart<T>>> createInfixFromTokens(const std::vector<Token> &tokens) const {
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

  std::unique_ptr<T> createExpressionFromPostfix(const std::vector<std::unique_ptr<OperationPart<T>>> &parts) const {
    std::stack<std::unique_ptr<T> > expressions;
    std::string lastAlias;
    std::string currentAlias;
    for (auto &part : parts) {
      if (part->type != ::OperationPartType::OPERAND && part->type != ::OperationPartType::LEFT_BRACKET
          && part->type != ::OperationPartType::RIGHT_BRACKET) {
        currentAlias = memory.generateNewAvailableAlias(lastAlias);
        lastAlias = currentAlias;
      }
      part->evaluate(expressions, currentAlias);
    }
    expressions.top()->reset();
    return std::move(expressions.top());
  }

/**
 * Create postfix ordering of OperationPart from infix using shunning-yard algorithm.
 * @param infix
 * @return
 */
  std::vector<std::unique_ptr<OperationPart<T>>> createPostfixFromInfix(std::vector<std::unique_ptr<OperationPart<T>>> &&infix) const {
    std::vector<std::unique_ptr<OperationPart<T> > > postfix;
    std::stack<std::unique_ptr<OperationPart<T> > > stack;
    for (size_t i = 0; i < infix.size(); i++) {
      if (infix[i]->type == ::OperationPartType::OPERAND) {
        postfix.push_back(std::move(infix[i]));
      } else if (infix[i]->type == ::OperationPartType::LEFT_BRACKET) {
        stack.push(std::move(infix[i]));
      } else if (infix[i]->type == ::OperationPartType::RIGHT_BRACKET) {
        bool bracketMatched = false;
        while (!stack.empty()) {
          if (stack.top()->type == ::OperationPartType::LEFT_BRACKET) {
            bracketMatched = true;
            stack.pop();
            break;
          } else {
            postfix.push_back(std::move(stack.top()));
            stack.pop();
          }
        }
        if (!bracketMatched) { // stack is empty now
          throw std::invalid_argument("Mismatched parentheses");
        }
      } else {
        while (!stack.empty() &&
            stack.top()->type != ::OperationPartType::LEFT_BRACKET &&
            stack.top()->type != ::OperationPartType::RIGHT_BRACKET &&
            stack.top()->priority >= infix[i]->priority) {
          postfix.push_back(std::move(stack.top()));
          stack.pop();
        }
        stack.push(std::move(infix[i]));
      }
    }
    while (!stack.empty()) {
      if (stack.top()->type == ::OperationPartType::LEFT_BRACKET
          || stack.top()->type == ::OperationPartType::RIGHT_BRACKET) {
        throw std::invalid_argument("Mismatched parentheses");
      }
      postfix.push_back(std::move(stack.top()));
      stack.pop();
    }
    return postfix;
  }
  VariablesMemory &memory;
  std::vector<std::unique_ptr<OperationPartFactory<T>>> factories;
};

#endif //SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
