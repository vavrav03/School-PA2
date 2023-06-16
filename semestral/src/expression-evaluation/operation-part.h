#ifndef SEMESTRAL_OPERATION_PART_H
#define SEMESTRAL_OPERATION_PART_H

#include "../user-interfaces/string-parsing/tokenizer/tokenizer.h"
#include "../data-sources/expressions/expressions.h"
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
  OperationPart(OperationPartType type, int priority) : type(type), priority(priority) {}

  const OperationPartType type;
  const int priority;
  virtual ~OperationPart() = default;

  virtual void evaluate(std::stack<std::unique_ptr<T>> &evaluatedParts) {
    // do nothing
  };
};

#endif //SEMESTRAL_OPERATION_PART_H
