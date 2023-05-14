#ifndef SEMESTRAL_BOOLEAN_EXPRESSION_H
#define SEMESTRAL_BOOLEAN_EXPRESSION_H

#include <vector>
#include <string>
#include "../abstract/data-row.h"

class BooleanExpression
{
public:
  BooleanExpression() = default;
  virtual bool evaluate() const = 0;
  virtual ~BooleanExpression() = default;
};

#endif // SEMESTRAL_BOOLEAN_EXPRESSION_H