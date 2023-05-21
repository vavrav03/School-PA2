#ifndef SEMESTRAL_UNARY_OPERATOR_EXPRESSION_H
#define SEMESTRAL_UNARY_OPERATOR_EXPRESSION_H

#include "./boolean-expression.h"

class UnaryOperatorExpression: public BooleanExpression
{
public:
  UnaryOperatorExpression(const BooleanExpression &expression): expression(expression) {}
  virtual bool evaluate() const = 0;
  ~UnaryOperatorExpression() = default;
protected:
  const BooleanExpression &expression;
};

class NotExpression: public UnaryOperatorExpression {
public:
  NotExpression(const BooleanExpression &expression): UnaryOperatorExpression(expression) {}
  bool evaluate(HeaderValueContainer &headerValues) const {
    return !expression.evaluate(headerValues);
  }
};

#endif //SEMESTRAL_UNARY_OPERATOR_EXPRESSION_H
