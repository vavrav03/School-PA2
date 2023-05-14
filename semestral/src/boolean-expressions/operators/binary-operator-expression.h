#ifndef SEMESTRAL_BINARY_OPERATOR_EXPRESSION_H
#define SEMESTRAL_BINARY_OPERATOR_EXPRESSION_H

#include "../boolean-expression/boolean-expression.h"

class BinaryOperatorExpression
{
public:
  BinaryOperatorExpression(const BooleanExpression &left, const BooleanExpression &right);
  virtual bool evaluate() const = 0;
  virtual ~BinaryOperatorExpression() = default;
protected:
  const BooleanExpression &left;
  const BooleanExpression &right;
};

#endif // SEMESTRAL_BINARY_OPERATOR_EXPRESSION_H