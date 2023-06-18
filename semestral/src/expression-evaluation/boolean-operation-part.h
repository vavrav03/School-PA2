#ifndef SEMESTRAL_SRC_EXPRESSION_EVALUATION_BOOLEAN_OPERATION_PART_H_
#define SEMESTRAL_SRC_EXPRESSION_EVALUATION_BOOLEAN_OPERATION_PART_H_

#include "./operation-part.h"
#include "../boolean-expressions/boolean-expressions.h"
#include "../boolean-expressions/primary-boolean-expressions.h"

template<typename T>
class BinaryPrimaryBooleanOperand : public OperationPart<AbstractBooleanExpression> {
 public:
  BinaryPrimaryBooleanOperand(const std::string &leftName, const std::string &rightName)
      : OperationPart<AbstractBooleanExpression>(OperationPartType::OPERAND, 999),
        leftName(leftName),
        rightName(rightName) {}

  void evaluate(std::vector<std::unique_ptr<AbstractBooleanExpression> > &evaluatedParts) override {
    evaluatedParts.push_back(std::make_unique<T>(std::move(leftName), std::move(rightName)));
  }

 protected:
  std::string leftName;
  std::string rightName;
};

class EqualOperand : public BinaryPrimaryBooleanOperand<EqualPrimaryBooleanExpression> {
 public:
  EqualOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand<EqualPrimaryBooleanExpression>(leftName, rightName) {}
};

class NoEqualOperand : public BinaryPrimaryBooleanOperand<NotEqualPrimaryBooleanExpression> {
 public:
  NoEqualOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand<NotEqualPrimaryBooleanExpression>(leftName, rightName) {}
};

class LessThanOperand : public BinaryPrimaryBooleanOperand<LessThanPrimaryBooleanExpression> {
 public:
  LessThanOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand<LessThanPrimaryBooleanExpression>(leftName, rightName) {}
};

class LessThanOrEqualOperand : public BinaryPrimaryBooleanOperand<LessThanOrEqualPrimaryBooleanExpression> {
 public:
  LessThanOrEqualOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand<LessThanOrEqualPrimaryBooleanExpression>(leftName, rightName) {}
};

class GreaterThanOperand : public BinaryPrimaryBooleanOperand<GreaterThanPrimaryBooleanExpression> {
 public:
  GreaterThanOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand<GreaterThanPrimaryBooleanExpression>(leftName, rightName) {}
};

class GreaterThanOrEqualOperand : public BinaryPrimaryBooleanOperand<GreaterThanOrEqualPrimaryBooleanExpression> {
 public:
  GreaterThanOrEqualOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand<GreaterThanOrEqualPrimaryBooleanExpression>(leftName, rightName) {}
};

class NotOperator : public UnaryOperator<AbstractBooleanExpression, NotBooleanExpression> {
 public:
  NotOperator() : UnaryOperator<AbstractBooleanExpression, NotBooleanExpression>(11) {}
};

class AndOperator :public BinaryOperator<AbstractBooleanExpression, AndBooleanExpression> {
 public:
  AndOperator() : BinaryOperator<AbstractBooleanExpression, AndBooleanExpression>(10) {}
};

class OrOperator : public BinaryOperator<AbstractBooleanExpression, OrBooleanExpression> {
 public:
  OrOperator() : BinaryOperator<AbstractBooleanExpression, OrBooleanExpression>(9) {}
};

class ImpliesOperator : public BinaryOperator<AbstractBooleanExpression, ImplicationBooleanExpression> {
 public:
  ImpliesOperator() : BinaryOperator<AbstractBooleanExpression, ImplicationBooleanExpression>(9) {}
};

class EquivalenceOperator : public BinaryOperator<AbstractBooleanExpression, EquivalenceBooleanExpression> {
 public:
  EquivalenceOperator() : BinaryOperator<AbstractBooleanExpression, EquivalenceBooleanExpression>(9) {}
};

class XorOperator : public BinaryOperator<AbstractBooleanExpression, XorBooleanExpression> {
 public:
  XorOperator() : BinaryOperator<AbstractBooleanExpression, XorBooleanExpression>(9) {}
};

class NorOperator : public BinaryOperator<AbstractBooleanExpression, NorBooleanExpression> {
 public:
  NorOperator() : BinaryOperator<AbstractBooleanExpression, NorBooleanExpression>(9) {}
};

class NandOperator : public BinaryOperator<AbstractBooleanExpression, NandBooleanExpression> {
 public:
  NandOperator() : BinaryOperator<AbstractBooleanExpression, NandBooleanExpression>(9) {}
};

#endif //SEMESTRAL_SRC_EXPRESSION_EVALUATION_BOOLEAN_OPERATION_PART_H_
