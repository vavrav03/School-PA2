#ifndef SEMESTRAL_EXPRESSIONS_H
#define SEMESTRAL_EXPRESSIONS_H

#include <string>
#include <iostream>
#include <initializer_list>
#include "../abstract.h"
#include "../../utils/utils.h"
#include "../../boolean-expressions/boolean-expressions.h"
#include <memory>

class AbstractBinaryExpression : public AbstractDataSource {
 public:
  AbstractBinaryExpression(std::unique_ptr<AbstractDataSource> leftExpression,
                           std::unique_ptr<AbstractDataSource> rightExpression)
      : AbstractDataSource(),
        leftExpression(std::move(leftExpression)),
        rightExpression(std::move(rightExpression)) {}

  void reset() override {
    leftExpression->reset();
    rightExpression->reset();
  }

  std::vector<std::string> getHeaderVector() const override {
    return leftExpression->getHeaderVector();
  }

  std::unordered_map<std::string, size_t> getHeaderMap() const override {
    return leftExpression->getHeaderMap();
  }

  size_t getHeaderIndex(const std::string &name) const override {
    return leftExpression->getHeaderIndex(name);
  }

  const std::string &getHeaderName(size_t index) const override {
    return leftExpression->getHeaderName(index);
  }

  size_t getHeaderSize() const override {
    return leftExpression->getHeaderSize();
  }

 protected:
  std::unique_ptr<AbstractDataSource> leftExpression;
  std::unique_ptr<AbstractDataSource> rightExpression;
};

class AbstractUnaryExpression : public AbstractDataSource {
 public:
  AbstractUnaryExpression(std::unique_ptr<AbstractDataSource> expression)
      : AbstractDataSource(), expression(std::move(expression)) {}

  void reset() override {
    expression->reset();
  }

  const std::vector<std::string> getNextRow() override {
    return expression->getNextRow();
  }

  std::vector<std::string> getHeaderVector() const override {
    return expression->getHeaderVector();
  }

  std::unordered_map<std::string, size_t> getHeaderMap() const override {
    return expression->getHeaderMap();
  }

  size_t getHeaderIndex(const std::string &name) const override {
    return expression->getHeaderIndex(name);
  }

  const std::string &getHeaderName(size_t index) const override {
    return expression->getHeaderName(index);
  }

  size_t getHeaderSize() const override {
    return expression->getHeaderSize();
  }

 protected:
  std::unique_ptr<AbstractDataSource> expression;
};

class ProjectionExpression : public AbstractUnaryExpression {
 public:
  ProjectionExpression(std::unique_ptr<AbstractDataSource> expression, const std::vector<std::string> &columns,
                       const std::unordered_map<std::string, std::string> &aliases);

  std::string toSQL() const override;
  std::vector<std::string> getHeaderVector() const override;
  std::unordered_map<std::string, size_t> getHeaderMap() const override;
  size_t getHeaderIndex(const std::string &name) const override;
  const std::string &getHeaderName(size_t index) const override;
  size_t getHeaderSize() const override;
  const std::vector<std::string> getNextRow() override;
  std::unique_ptr<AbstractDataSource> clone() const override;
 private:
  std::unordered_map<std::string, size_t> headerMap;
  std::unordered_map<std::string, std::string> aliasToPreviousName;
  std::string getWrappedColumnName(const std::string &name) const;
};

class IntersectionExpression : public AbstractBinaryExpression {
 public:
  IntersectionExpression(std::unique_ptr<AbstractDataSource> leftExpression,
                         std::unique_ptr<AbstractDataSource> rightExpression);
  std::string toSQL() const override;
  void reset() override;
  const std::vector<std::string> getNextRow() override;
  std::unique_ptr<AbstractDataSource> clone() const override;
};

class UnionExpression : public AbstractBinaryExpression {
 public:
  UnionExpression(std::unique_ptr<AbstractDataSource> leftExpression,
                  std::unique_ptr<AbstractDataSource> rightExpression);

  std::string toSQL() const override;
  void reset() override;
  const std::vector<std::string> getNextRow() override;
  std::unique_ptr<AbstractDataSource> clone() const override;
};

class ExceptExpression : public AbstractBinaryExpression {
 public:
  ExceptExpression(std::unique_ptr<AbstractDataSource> leftExpression,
                   std::unique_ptr<AbstractDataSource> rightExpression);

  std::string toSQL() const override;
  void reset() override;
  const std::vector<std::string> getNextRow() override;
  std::unique_ptr<AbstractDataSource> clone() const override;
};

class CartesianProductExpression : public AbstractBinaryExpression {
 public:
  CartesianProductExpression(std::unique_ptr<AbstractDataSource> leftExpression,
                             std::unique_ptr<AbstractDataSource> rightExpression);

  std::string toSQL() const override;
  void reset() override;
  const std::vector<std::string> getNextRow() override;
  std::vector<std::string> getHeaderVector() const override;
  std::unordered_map<std::string, size_t> getHeaderMap() const override;
  size_t getHeaderIndex(const std::string &name) const override;
  const std::string &getHeaderName(size_t index) const override;
  size_t getHeaderSize() const override;
  std::unique_ptr<AbstractDataSource> clone() const override;
 private:
  std::vector<std::string> currentLeftRow;
};

class NaturalJoinExpression : public AbstractBinaryExpression {
 public:
  NaturalJoinExpression(std::unique_ptr<AbstractDataSource> leftExpression,
                        std::unique_ptr<AbstractDataSource> rightExpression);

  std::string toSQL() const override;
  void reset() override;
  const std::vector<std::string> getNextRow() override;
  std::vector<std::string> getHeaderVector() const override;
  std::unordered_map<std::string, size_t> getHeaderMap() const override;
  size_t getHeaderIndex(const std::string &name) const override;
  const std::string &getHeaderName(size_t index) const override;
  size_t getHeaderSize() const override;
  std::unique_ptr<AbstractDataSource> clone() const override;
 private:
  std::vector<std::string> currentLeftRow;
  std::vector<std::string> sameColumns;
  std::unordered_map<std::string, size_t> headerMap;
};

class SelectionExpression : public AbstractUnaryExpression {
 public:
  SelectionExpression(std::unique_ptr<AbstractDataSource> expression, std::unique_ptr<AbstractBooleanExpression> condition);

  std::string toSQL() const override;
  const std::vector<std::string> getNextRow() override;
  std::unique_ptr<AbstractDataSource> clone() const override;
 private:
  std::unique_ptr<AbstractBooleanExpression> condition;
};

#endif //SEMESTRAL_EXPRESSIONS_H
