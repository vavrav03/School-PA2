#ifndef SEMESTRAL_HIGHER_OR_EQUAL_EXPRESSION_H
#define SEMESTRAL_HIGHER_OR_EQUAL_EXPRESSION_H

#include "../binary-primary-expression.h"

class HigherOrEqualExpression: public BinaryBooleanExpression {

public:
  HigherOrEqualExpression(const std::string &headerColumn1, const std::string &headerColumn2);
  bool evaluate(HeaderValueContainer &headerValues) const override;
};

#endif //SEMESTRAL_HIGHER_OR_EQUAL_EXPRESSION_H