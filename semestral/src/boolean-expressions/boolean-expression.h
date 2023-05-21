#ifndef SEMESTRAL_BOOLEAN_EXPRESSION_H
#define SEMESTRAL_BOOLEAN_EXPRESSION_H

#include <vector>
#include <string>
#include "../data-sources/abstract/header-value-container.h"

class BooleanExpression
{
public:
  BooleanExpression() = default;
  virtual bool evaluate(HeaderValueContainer & headerValues) const = 0;
  ~BooleanExpression() = default;
  virtual std::string toSQL() const = 0;
};

#endif // SEMESTRAL_BOOLEAN_EXPRESSION_H