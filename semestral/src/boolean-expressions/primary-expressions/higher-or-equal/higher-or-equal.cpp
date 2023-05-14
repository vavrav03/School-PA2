
#include "./higher-or-equal.h"

using namespace std;

HigherOrEqualExpression::HigherOrEqualExpression(const string &headerColumn1, const string &headerColumn2) : BinaryBooleanExpression(headerColumn1, headerColumn2){}

bool HigherOrEqualExpression::evaluate(HeaderValueContainer &headerValues) const {
  return headerValues[headerColumn1] >= headerValues[headerColumn2];
}

