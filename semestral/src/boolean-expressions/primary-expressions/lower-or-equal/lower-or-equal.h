#ifndef SEMESTRAL_LOWER_OR_EQUAL_H
#define SEMESTRAL_LOWER_OR_EQUAL_H

#include "../binary-primary-expression.h"
#include <string>

class LowerOrEqualExpression: public BinaryBooleanExpression {

public:
  LowerOrEqualExpression(const std::string &headerColumn1, const std::string &headerColumn2);
  bool evaluate(HeaderValueContainer &headerValues) const override;
};

#endif //SEMESTRAL_LOWER_OR_EQUAL_H