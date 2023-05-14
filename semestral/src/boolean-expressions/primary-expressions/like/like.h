#ifndef SEMESTRAL_LIKE_EXPRESSION_H
#define SEMESTRAL_LIKE_EXPRESSION_H

#include "../binary-primary-expression.h"

class LikeExpression : public BinaryBooleanExpression {

public:
  LikeExpression(const std::string &headerColumn1, const std::string &regex);
  bool evaluate(HeaderValueContainer &headerValues) const override;
};

#endif //SEMESTRAL_LIKE_EXPRESSION_H