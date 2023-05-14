#include "./lower-or-equal.h"

using namespace std;

LowerOrEqualExpression::LowerOrEqualExpression(const string &headerColumn1, const string &headerColumn2) : BinaryBooleanExpression(headerColumn1, headerColumn2){}

bool LowerOrEqualExpression::evaluate(HeaderValueContainer &headerValues) const {
  return headerValues[headerColumn1] <= headerValues[headerColumn2];
}
