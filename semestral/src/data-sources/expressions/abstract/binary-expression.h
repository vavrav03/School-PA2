#ifndef SEMESTRAL_BINARY_EXPRESSION_H
#define SEMESTRAL_BINARY_EXPRESSION_H

#include "./expression.h"

class AbstractBinaryExpression : public AbstractExpression
{
public:
  AbstractBinaryExpression(AbstractExpression *_left, AbstractExpression *_right)
      : left(_left), right(_right) {}

protected:
  AbstractExpression *left;
  AbstractExpression *right;
};

#endif // SEMESTRAL_BINARY_EXPRESSION_H