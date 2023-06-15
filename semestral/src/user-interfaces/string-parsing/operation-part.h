#ifndef SEMESTRAL_OPERATION_PART_H
#define SEMESTRAL_OPERATION_PART_H

#include "tokenizer/tokenizer.h"
#include "../../data-sources/expressions/expressions.h"
#include <stack>
#include <iostream>

enum class OperationPartType {
  OPERAND,
  PREFIX_UNARY_OPERATOR,
  POSTFIX_UNARY_OPERATOR,
  BINARY_OPERATOR,
  LEFT_BRACKET,
  RIGHT_BRACKET
};

template<typename T>
class OperationPart {

 public:
  OperationPart(OperationPartType type, int priority) : type(type),
                                                        priority(priority) {}

  const OperationPartType type;
  const int priority;
  virtual ~OperationPart() = default;

  virtual void evaluate(std::stack<std::unique_ptr<T>> &evaluatedParts, std::string &operationAlias) {
    // do nothing
  };
};

template<typename T>
class OperationPartFactory {

 public:
  OperationPartFactory() {}

  /**
   * This method create OperationPart. It assumes that canCreate() returned true - no validity checks are performed
   * It also sets new value of nextTokenIndex
   * @param tokens
   * @param nextTokenIndex It is guaranteed to never exceed tokens.size(). Item with this index potentially belongs to this operation part
   * @return
   */
  virtual bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const = 0;
  virtual std::unique_ptr<OperationPart<T>> create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const = 0;
  virtual ~OperationPartFactory() = default;
};

/**
 * Create postfix ordering of OperationPart from infix using shunning-yard algorithm.
 * @param infix
 * @return
 */
template<typename T>
std::vector<std::unique_ptr<OperationPart<T>>> createPostfixFromInfix(std::vector<std::unique_ptr<OperationPart<T>>> &&infix){
  std::vector<std::unique_ptr<OperationPart<T> > > postfix;
  std::stack<std::unique_ptr<OperationPart<T> > > stack;
  for (size_t i = 0; i < infix.size(); i++) {
    if (infix[i]->type == OperationPartType::OPERAND) {
      postfix.push_back(std::move(infix[i]));
    } else if (infix[i]->type == OperationPartType::LEFT_BRACKET) {
      stack.push(std::move(infix[i]));
    } else if (infix[i]->type == OperationPartType::RIGHT_BRACKET) {
      bool bracketMatched = false;
      while (!stack.empty()) {
        if (stack.top()->type == OperationPartType::LEFT_BRACKET) {
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
          stack.top()->type != OperationPartType::LEFT_BRACKET &&
          stack.top()->type != OperationPartType::RIGHT_BRACKET &&
          stack.top()->priority >= infix[i]->priority) {
        postfix.push_back(std::move(stack.top()));
        stack.pop();
      }
      stack.push(std::move(infix[i]));
    }
  }
  while (!stack.empty()) {
    if (stack.top()->type == OperationPartType::LEFT_BRACKET
        || stack.top()->type == OperationPartType::RIGHT_BRACKET) {
      throw std::invalid_argument("Mismatched parentheses");
    }
    postfix.push_back(std::move(stack.top()));
    stack.pop();
  }
  return postfix;
}

#endif //SEMESTRAL_OPERATION_PART_H
