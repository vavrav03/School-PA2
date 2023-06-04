#ifndef SEMESTRAL_BINARY_OPERATOR_EXPRESSION_H
#define SEMESTRAL_BINARY_OPERATOR_EXPRESSION_H

#include "./boolean-expression.h"

class BinaryOperatorExpression
{
public:
  BinaryOperatorExpression(const BooleanExpression &left, const BooleanExpression &right) : left(left), right(right) {}
  virtual bool evaluate() const = 0;
  ~BinaryOperatorExpression() = default;
protected:
  const BooleanExpression &left;
  const BooleanExpression &right;
};

class AndExpression: public BinaryOperatorExpression {

public:
  AndExpression(const BooleanExpression &left, const BooleanExpression &right): BinaryOperatorExpression(left, right) {}
  bool evaluate(HeaderValueContainer &headerValues) const {
    return left.evaluate(headerValues) && right.evaluate(headerValues);
  }
};

class OrExpression: public BinaryOperatorExpression {

public:
  OrExpression(const BooleanExpression &left, const BooleanExpression &right): BinaryOperatorExpression(left, right) {}
  bool evaluate(HeaderValueContainer &headerValues) const {
    return left.evaluate(headerValues) || right.evaluate(headerValues);
  }
};

class XorExpression: public BinaryOperatorExpression {

public:
  XorExpression(const BooleanExpression &left, const BooleanExpression &right): BinaryOperatorExpression(left, right) {}
  bool evaluate(HeaderValueContainer &headerValues) const {
    return left.evaluate(headerValues) ^ right.evaluate(headerValues);
  }
};

#endif // SEMESTRAL_BINARY_OPERATOR_EXPRESSION_H