
#ifndef SEMESTRAL_ABSTRACT_EXPRESSION_H
#define SEMESTRAL_ABSTRACT_EXPRESSION_H

#include "../../abstract/abstract.h"

class AbstractExpression : public AbstractDataSource
{
public:
  AbstractExpression() = default;
  virtual ~AbstractExpression() = default;
  virtual std::string toSQL() const = 0;
};

#endif // SEMESTRAL_ABSTRACT_EXPRESSION_H
