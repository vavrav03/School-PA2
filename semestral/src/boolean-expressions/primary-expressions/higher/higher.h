#ifndef SEMESTRAL_HIGHER_EXPRESSION_H
#define SEMESTRAL_HIGHER_EXPRESSION_H

#include "../binary-primary-expression.h"

class HigherExpression: public BinaryBooleanExpression {

public:
  HigherExpression(const std::string &headerColumn1, const std::string &headerColumn2);
  bool evaluate(HeaderValueContainer &headerValues) const override;
};

#endif //SEMESTRAL_HIGHER_EXPRESSION_H