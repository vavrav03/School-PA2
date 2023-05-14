#include "./higher.h"

using namespace std;

HigherExpression::HigherExpression(const string &headerColumn1, const string &headerColumn2) : BinaryBooleanExpression(headerColumn1, headerColumn2){}

bool HigherExpression::evaluate(HeaderValueContainer &headerValues) const {
  return headerValues[headerColumn1] > headerValues[headerColumn2];
}