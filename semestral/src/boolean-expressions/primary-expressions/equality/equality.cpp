#include "./equality.h"

using namespace std;

EqualityExpression::EqualityExpression(const string &headerColumn1, const string &headerColumn2) : BinaryBooleanExpression(headerColumn1, headerColumn2){}

bool EqualityExpression::evaluate(HeaderValueContainer &headerValues) const {
  return headerValues[headerColumn1] == headerValues[headerColumn2];
}
