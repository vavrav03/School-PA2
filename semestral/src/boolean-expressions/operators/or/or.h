#ifndef SEMESTRAL_OR_EXPRESSION_H
#define SEMESTRAL_OR_EXPRESSION_H

#include "../../boolean-expression/boolean-expression.h"
#include <string>

class OrExpression: public BooleanExpression {

public:
  OrExpression(const BooleanExpression &left, const BooleanExpression &right);
  bool evaluate(HeaderValueContainer &headerValues) const override;
  ~OrExpression() override = default;
};

#endif //SEMESTRAL_OR_EXPRESSION_H