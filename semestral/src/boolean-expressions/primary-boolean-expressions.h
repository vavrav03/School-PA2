#ifndef SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_PRIMARY_BOOLEAN_EXPRESSIONS_H_
#define SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_PRIMARY_BOOLEAN_EXPRESSIONS_H_

#include <string>
#include "./header-row-mapping.h"
#include "./boolean-expressions.h"

/**
 * All expression that do not take boolean as input and spit out boolean that are used in SQL queries must inherit from this class
 *
 */
class AbstractPrimaryBooleanExpression : public AbstractBooleanExpression {
 public:
  AbstractPrimaryBooleanExpression(const std::string &leftName, const std::string &rightName)
      : leftName(leftName), rightName(rightName) {}
  virtual ~AbstractPrimaryBooleanExpression() {}
 protected:
  std::string leftName;
  std::string rightName;
};

class EqualPrimaryBooleanExpression : public AbstractPrimaryBooleanExpression {
 public:
  EqualPrimaryBooleanExpression(const std::string &leftName, const std::string &rightName)
      : AbstractPrimaryBooleanExpression(leftName, rightName) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return rowMapping.getValue(leftName) == rowMapping.getValue(rightName);
  }
  std::string toSQL() override {
    return leftName + " = " + rightName;
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<EqualPrimaryBooleanExpression>(leftName, rightName);
  }
};

class NotEqualPrimaryBooleanExpression : public AbstractPrimaryBooleanExpression {
 public:
  NotEqualPrimaryBooleanExpression(const std::string &leftName, const std::string &rightName)
      : AbstractPrimaryBooleanExpression(leftName, rightName) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return rowMapping.getValue(leftName) != rowMapping.getValue(rightName);
  }
  std::string toSQL() override {
    return leftName + " != " + rightName;
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<NotEqualPrimaryBooleanExpression>(leftName, rightName);
  }
};

class LessThanPrimaryBooleanExpression : public AbstractPrimaryBooleanExpression {
 public:
  LessThanPrimaryBooleanExpression(const std::string &leftName, const std::string &rightName)
      : AbstractPrimaryBooleanExpression(leftName, rightName) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return rowMapping.getValue(leftName) < rowMapping.getValue(rightName);
  }
  std::string toSQL() override {
    return leftName + " < " + rightName;
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<LessThanPrimaryBooleanExpression>(leftName, rightName);
  }
};

class LessThanOrEqualPrimaryBooleanExpression : public AbstractPrimaryBooleanExpression {
 public:
  LessThanOrEqualPrimaryBooleanExpression(const std::string &leftName, const std::string &rightName)
      : AbstractPrimaryBooleanExpression(leftName, rightName) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return rowMapping.getValue(leftName) <= rowMapping.getValue(rightName);
  }
  std::string toSQL() override {
    return leftName + " <= " + rightName;
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<LessThanOrEqualPrimaryBooleanExpression>(leftName, rightName);
  }
};

class GreaterThanPrimaryBooleanExpression : public AbstractPrimaryBooleanExpression {
 public:
  GreaterThanPrimaryBooleanExpression(const std::string &leftName, const std::string &rightName)
      : AbstractPrimaryBooleanExpression(leftName, rightName) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return rowMapping.getValue(leftName) > rowMapping.getValue(rightName);
  }
  std::string toSQL() override {
    return leftName + " > " + rightName;
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<GreaterThanPrimaryBooleanExpression>(leftName, rightName);
  }
};

class GreaterThanOrEqualPrimaryBooleanExpression : public AbstractPrimaryBooleanExpression {
 public:
  GreaterThanOrEqualPrimaryBooleanExpression(const std::string &leftName, const std::string &rightName)
      : AbstractPrimaryBooleanExpression(leftName, rightName) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return rowMapping.getValue(leftName) >= rowMapping.getValue(rightName);
  }
  std::string toSQL() override {
    return leftName + " >= " + rightName;
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<GreaterThanOrEqualPrimaryBooleanExpression>(leftName, rightName);
  }
};

#endif //SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_PRIMARY_BOOLEAN_EXPRESSIONS_H_
