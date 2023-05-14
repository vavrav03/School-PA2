#ifndef SEMESTRAL_BINARY_BOOLEAN_EXPRESSION_H
#define SEMESTRAL_BINARY_BOOLEAN_EXPRESSION_H

#include <string>
#include "../boolean-expression/boolean-expression.h"

/**
* These expressions are used to convert string records to boolean values based on some rules in a boolean expression
*/
class BinaryBooleanExpression: public BooleanExpression
{
public:
  BinaryBooleanExpression(const std::string &headerColumn1, const std::string &headerColumn2);
protected:
  std::string headerColumn1;
  std::string headerColumn2;
};

#endif // SEMESTRAL_BINARY_BOOLEAN_EXPRESSION_H