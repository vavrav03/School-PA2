#ifndef SEMESTRAL_BINARY_EXPRESSION_H
#define SEMESTRAL_BINARY_EXPRESSION_H

#include "./expression.h"

class AbstractUnaryExpression : public AbstractExpression {
public:
  AbstractUnaryExpression(AbstractDataSource *_expression)
          : expression(_expression) {}

  virtual ~AbstractUnaryExpression() {
    delete expression;
  }

protected:
  AbstractDataSource *expression;
};

#endif // SEMESTRAL_BINARY_EXPRESSION_H