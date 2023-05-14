#include "./lower.h"

using namespace std;

LowerExpression::LowerExpression(const string &headerColumn1, const string &headerColumn2) : BinaryBooleanExpression(headerColumn1, headerColumn2){}

bool LowerExpression::evaluate(HeaderValueContainer &headerValues) const {
  return headerValues[headerColumn1] < headerValues[headerColumn2];
}
