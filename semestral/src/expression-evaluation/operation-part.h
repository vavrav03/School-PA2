#ifndef SEMESTRAL_OPERATION_PART_H
#define SEMESTRAL_OPERATION_PART_H

#include "../user-interfaces/string-parsing/tokenizer/tokenizer.h"
#include "../data-sources/expressions/expressions.h"
#include <vector>
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

  virtual void evaluate(std::vector<std::unique_ptr<T>> &evaluatedParts) {
    // do nothing
  };
};

class LeftBracketOperand : public OperationPart<AbstractDataSource> {
 public:
  LeftBracketOperand() : OperationPart<AbstractDataSource>(OperationPartType::LEFT_BRACKET, 999) {}
};

class RightBracketOperand : public OperationPart<AbstractDataSource> {
 public:
  RightBracketOperand() : OperationPart<AbstractDataSource>(OperationPartType::RIGHT_BRACKET, 999) {}
};

template<typename GenericType, typename TargetType>
class BinaryOperator : public OperationPart<GenericType> {
 public:
  BinaryOperator(int priority) : OperationPart<GenericType>(OperationPartType::BINARY_OPERATOR, priority) {}

  void evaluate(std::vector<std::unique_ptr<GenericType>> &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<TargetType>(std::move(left), std::move(right)));
  }
};

#endif //SEMESTRAL_OPERATION_PART_H
