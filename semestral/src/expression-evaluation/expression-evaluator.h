#ifndef SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
#define SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H

#include <vector>
#include "relational-operation-part.h"
#include "./operation-part.h"
#include "../user-interfaces/variables-memory/variables-memory.h"

template<typename T>
class ExpressionEvaluator {
 public:
  ExpressionEvaluator(VariablesMemory &memory) : memory(memory) {}

  std::unique_ptr<T> createExpressionFromPostfix(const std::vector<std::unique_ptr<OperationPart<T>>> &parts) const {
    std::stack<std::unique_ptr<T> > expressions;
    for (auto &part : parts) {
      part->evaluate(expressions);
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
 private:
  VariablesMemory &memory;
};

#endif //SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
