#ifndef SEMESTRAL_AND_EXPRESSION_H
#define SEMESTRAL_AND_EXPRESSION_H

#include "../../boolean-expression/boolean-expression.h"
#include <string>

class AndExpression: public BooleanExpression {

public:
  AndExpression(const BooleanExpression &left, const BooleanExpression &right);
  bool evaluate(HeaderValueContainer &headerValues) const override;
  ~AndExpression() override = default;
};

#endif //SEMESTRAL_AND_EXPRESSION_H