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
    std::vector<std::unique_ptr<T> > expressions;
    for (auto &part : parts) {
      part->evaluate(expressions);
    }
    expressions.back()->reset();
    return std::move(expressions.back());
  }

/**
 * Create postfix ordering of OperationPart from infix using shunning-yard algorithm.
 * @param infix
 * @return
 */
  std::vector<std::unique_ptr<OperationPart<T>>> createPostfixFromInfix(std::vector<std::unique_ptr<OperationPart<T>>> &&infix) const {
    std::vector<std::unique_ptr<OperationPart<T> > > postfix;
    std::vector<std::unique_ptr<OperationPart<T> > > vector;
    for (size_t i = 0; i < infix.size(); i++) {
      if (infix[i]->type == ::OperationPartType::OPERAND) {
        postfix.push_back(std::move(infix[i]));
      } else if (infix[i]->type == ::OperationPartType::LEFT_BRACKET) {
        vector.push_back(std::move(infix[i]));
      } else if (infix[i]->type == ::OperationPartType::RIGHT_BRACKET) {
        bool bracketMatched = false;
        while (!vector.empty()) {
          if (vector.back()->type == ::OperationPartType::LEFT_BRACKET) {
            bracketMatched = true;
            vector.pop_back();
            break;
          } else {
            postfix.push_back(std::move(vector.back()));
            vector.pop_back();
          }
        }
        if (!bracketMatched) { // vector is empty now
          throw std::invalid_argument("Mismatched parentheses");
        }
      } else {
        while (!vector.empty() &&
            vector.back()->type != ::OperationPartType::LEFT_BRACKET &&
            vector.back()->type != ::OperationPartType::RIGHT_BRACKET &&
            vector.back()->priority >= infix[i]->priority) {
          postfix.push_back(std::move(vector.back()));
          vector.pop_back();
        }
        vector.push_back(std::move(infix[i]));
      }
    }
    while (!vector.empty()) {
      if (vector.back()->type == ::OperationPartType::LEFT_BRACKET
          || vector.back()->type == ::OperationPartType::RIGHT_BRACKET) {
        throw std::invalid_argument("Mismatched parentheses");
      }
      postfix.push_back(std::move(vector.back()));
      vector.pop_back();
    }
    return postfix;
  }
 private:
  VariablesMemory &memory;
};

#endif //SEMESTRAL_RELATIONAL_EXPRESSION_PARSER_H
