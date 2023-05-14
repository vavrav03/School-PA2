#include "./like.h"
#include <regex>
#include <string>
#include <iostream>

using namespace std;

LikeExpression::LikeExpression(const string &headerColumn1, const string &headerColumn2) : BinaryBooleanExpression(headerColumn1, headerColumn2){}

bool LikeExpression::evaluate(HeaderValueContainer &headerValues) const {
  const string & regexString = headerColumn2; // headerColumn2 is regex
  return regex_match(headerValues[headerColumn1], regex(regexString));
}