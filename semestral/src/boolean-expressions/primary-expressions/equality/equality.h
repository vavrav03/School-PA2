#ifndef SEMESTRAL_EQUALITY_H
#define SEMESTRAL_EQUALITY_H

#include "../binary-primary-expression.h"

class EqualityExpression: public BinaryBooleanExpression {

public:
  EqualityExpression(const std::string &headerColumn1, const std::string &headerColumn2);
  bool evaluate(HeaderValueContainer &headerValues) const override;
};

#endif //SEMESTRAL_EQUALITY_H