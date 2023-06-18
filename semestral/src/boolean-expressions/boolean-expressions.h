#ifndef SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_BOOLEAN_EXPRESSIONS_H_
#define SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_BOOLEAN_EXPRESSIONS_H_

#include "./header-row-mapping.h"
#include <string>
#include <memory>

/**
 * All expressions that take anything and spit out boolean that are used in SQL queries must inherit from this class
 */
class AbstractBooleanExpression {
 public:
  virtual bool evaluate(const HeaderRowMapping &rowMapping) = 0;
  virtual std::string toSQL() = 0;
  virtual std::unique_ptr<AbstractBooleanExpression> clone() = 0;
  virtual ~AbstractBooleanExpression() = default;
};

class AbstractUnaryBooleanExpression : public AbstractBooleanExpression {
 public:
  explicit AbstractUnaryBooleanExpression(std::unique_ptr<AbstractBooleanExpression> expression)
      : expression(std::move(expression)) {}
 protected:
  std::unique_ptr<AbstractBooleanExpression> expression;
};

class AbstractBinaryBooleanExpression : public AbstractBooleanExpression {
 public:
  AbstractBinaryBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                                  std::unique_ptr<AbstractBooleanExpression> right)
      : left(std::move(left)), right(std::move(right)) {}
 protected:
  std::unique_ptr<AbstractBooleanExpression> left;
  std::unique_ptr<AbstractBooleanExpression> right;
};

class AndBooleanExpression : public AbstractBinaryBooleanExpression {
 public:
  AndBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                       std::unique_ptr<AbstractBooleanExpression> right)
      : AbstractBinaryBooleanExpression(std::move(left), std::move(right)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return left->evaluate(rowMapping) && right->evaluate(rowMapping);
  }
  std::string toSQL() override {
    return "(" + left->toSQL() + ")" + " AND " + "(" + right->toSQL() + ")";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<AndBooleanExpression>(left->clone(), right->clone());
  }
};

class OrBooleanExpression : public AbstractBinaryBooleanExpression {
 public:
  OrBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                      std::unique_ptr<AbstractBooleanExpression> right)
      : AbstractBinaryBooleanExpression(std::move(left), std::move(right)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return left->evaluate(rowMapping) || right->evaluate(rowMapping);
  }
  std::string toSQL() override {
    return "(" + left->toSQL() + ")" + " OR " + "(" + right->toSQL() + ")";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<OrBooleanExpression>(left->clone(), right->clone());
  }
};

class NotBooleanExpression : public AbstractUnaryBooleanExpression {
 public:
  explicit NotBooleanExpression(std::unique_ptr<AbstractBooleanExpression> expression)
      : AbstractUnaryBooleanExpression(std::move(expression)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return !expression->evaluate(rowMapping);
  }
  std::string toSQL() override {
    return "NOT (" + expression->toSQL() + ")";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<NotBooleanExpression>(expression->clone());
  }
};

class ImplicationBooleanExpression : public AbstractBinaryBooleanExpression {
 public:
  ImplicationBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                               std::unique_ptr<AbstractBooleanExpression> right)
      : AbstractBinaryBooleanExpression(std::move(left), std::move(right)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return !left->evaluate(rowMapping) || right->evaluate(rowMapping);
  }
  std::string toSQL() override {
    return "( NOT (" + left->toSQL() + ")" + ")" + " OR " + "(" + right->toSQL() + ")";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<ImplicationBooleanExpression>(left->clone(), right->clone());
  }
};

class EquivalenceBooleanExpression : public AbstractBinaryBooleanExpression {
 public:
  EquivalenceBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                               std::unique_ptr<AbstractBooleanExpression> right)
      : AbstractBinaryBooleanExpression(std::move(left), std::move(right)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return left->evaluate(rowMapping) == right->evaluate(rowMapping);
  }
  std::string toSQL() override {
    return "(" + left->toSQL() + ")" + " = " + "(" + right->toSQL() + ")";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<EquivalenceBooleanExpression>(left->clone(), right->clone());
  }
};

class XorBooleanExpression : public AbstractBinaryBooleanExpression {
 public:
  XorBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                       std::unique_ptr<AbstractBooleanExpression> right)
      : AbstractBinaryBooleanExpression(std::move(left), std::move(right)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return left->evaluate(rowMapping) != right->evaluate(rowMapping);
  }
  std::string toSQL() override {
    return "(" + left->toSQL() + ")" + " <> " + "(" + right->toSQL() + ")";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<XorBooleanExpression>(left->clone(), right->clone());
  }
};

class NandBooleanExpression : public AbstractBinaryBooleanExpression {
 public:
  NandBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                        std::unique_ptr<AbstractBooleanExpression> right)
      : AbstractBinaryBooleanExpression(std::move(left), std::move(right)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return !(left->evaluate(rowMapping) && right->evaluate(rowMapping));
  }
  std::string toSQL() override {
    return "(NOT (" + left->toSQL() + ")" + ") OR (" + "NOT (" + right->toSQL() + "))";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<NandBooleanExpression>(left->clone(), right->clone());
  }
};

class NorBooleanExpression : public AbstractBinaryBooleanExpression {
 public:
  NorBooleanExpression(std::unique_ptr<AbstractBooleanExpression> left,
                       std::unique_ptr<AbstractBooleanExpression> right)
      : AbstractBinaryBooleanExpression(std::move(left), std::move(right)) {}
  bool evaluate(const HeaderRowMapping &rowMapping) override {
    return !(left->evaluate(rowMapping) || right->evaluate(rowMapping));
  }
  std::string toSQL() override {
    return "(NOT (" + left->toSQL() + ")" + ") AND (" + "NOT (" + right->toSQL() + "))";
  }
  std::unique_ptr<AbstractBooleanExpression> clone() override {
    return std::make_unique<NorBooleanExpression>(left->clone(), right->clone());
  }
};

#endif //SEMESTRAL_SRC_BOOLEAN_EXPRESSIONS_BOOLEAN_EXPRESSIONS_H_
