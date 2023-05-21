#ifndef SEMESTRAL_BINARY_BOOLEAN_EXPRESSION_H
#define SEMESTRAL_BINARY_BOOLEAN_EXPRESSION_H

#include <string>
#include <regex>
#include "./boolean-expression.h"

/**
* These expressions are used to convert string records to boolean values based on some rules in a boolean expression
*/
class BinaryBooleanExpression : public BooleanExpression {
public:
  BinaryBooleanExpression(const std::string &headerColumn1, const std::string &headerColumn2) : headerColumn1(
          headerColumn1), headerColumn2(headerColumn2) {}

protected:
  std::string headerColumn1;
  std::string headerColumn2;
};

class LowerOrEqualExpression : public BinaryBooleanExpression {

public:
  LowerOrEqualExpression(const std::string &headerColumn1, const std::string &headerColumn2) : BinaryBooleanExpression(
          headerColumn1, headerColumn2) {}

  bool evaluate(HeaderValueContainer &headerValues) const override {
    return headerValues[headerColumn1] <= headerValues[headerColumn2];
  }
};

class LowerExpression : public BinaryBooleanExpression {

public:
  LowerExpression(const std::string &headerColumn1, const std::string &headerColumn2) : BinaryBooleanExpression(
          headerColumn1, headerColumn2) {}

  bool evaluate(HeaderValueContainer &headerValues) const override {
    return headerValues[headerColumn1] < headerValues[headerColumn2];
  }
};

class LikeExpression : public BinaryBooleanExpression {

public:
  LikeExpression(const std::string &headerColumn1, const std::string &regex) : BinaryBooleanExpression(headerColumn1,
                                                                                                       regex) {}

  bool evaluate(HeaderValueContainer &headerValues) const override {
    const std::string &regexString = headerColumn2; // headerColumn2 is regex
    return regex_match(headerValues[headerColumn1], std::regex(regexString));
  }

};

class HigherOrEqualExpression : public BinaryBooleanExpression {

public:
  HigherOrEqualExpression(const std::string &headerColumn1, const std::string &headerColumn2) : BinaryBooleanExpression(
          headerColumn1, headerColumn2) {}

  bool evaluate(HeaderValueContainer &headerValues) const override {
    return headerValues[headerColumn1] >= headerValues[headerColumn2];
  }
};

class HigherExpression : public BinaryBooleanExpression {

public:
  HigherExpression(const std::string &headerColumn1, const std::string &headerColumn2) : BinaryBooleanExpression(
          headerColumn1, headerColumn2) {}

  bool evaluate(HeaderValueContainer &headerValues) const override {
    return headerValues[headerColumn1] > headerValues[headerColumn2];
  }
};

class EqualityExpression : public BinaryBooleanExpression {

public:
  EqualityExpression(const std::string &headerColumn1, const std::string &headerColumn2) : BinaryBooleanExpression(
          headerColumn1, headerColumn2) {}

  bool evaluate(HeaderValueContainer &headerValues) const override {
    return headerValues[headerColumn1] == headerValues[headerColumn2];
  }
};

#endif // SEMESTRAL_BINARY_BOOLEAN_EXPRESSION_H