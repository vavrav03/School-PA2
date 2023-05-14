#ifndef SEMESTRAL_LOWER_EXPRESSION_H
#define SEMESTRAL_LOWER_EXPRESSION_H

#include "../binary-primary-expression.h"
#include <string>

class LowerExpression: public BinaryBooleanExpression {

public:
  LowerExpression(const std::string &headerColumn1, const std::string &headerColumn2);
  bool evaluate(HeaderValueContainer &headerValues) const override;
};

#endif //SEMESTRAL_LOWER_EXPRESSION_H