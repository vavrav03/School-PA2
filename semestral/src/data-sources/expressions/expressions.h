#ifndef SEMESTRAL_EXPRESSIONS_H
#define SEMESTRAL_EXPRESSIONS_H

#include <string>
#include <iostream>
#include <initializer_list>
#include "../abstract.h"
#include "../../utils/utils.h"
#include <memory>

class AbstractBinaryExpression : public AbstractDataSource {
public:
  AbstractBinaryExpression(std::shared_ptr<AbstractDataSource> leftExpression,
                           std::shared_ptr<AbstractDataSource> rightExpression,
                           const std::string &name)
          : AbstractDataSource(name), leftExpression(leftExpression), rightExpression(rightExpression) {}

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
  std::shared_ptr<AbstractDataSource> leftExpression;
  std::shared_ptr<AbstractDataSource> rightExpression;
};

class AbstractUnaryExpression : public AbstractDataSource {
public:
  AbstractUnaryExpression(std::shared_ptr<AbstractDataSource> expression, const std::string &name) : AbstractDataSource(
          name), expression(expression) {}

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
  std::shared_ptr<AbstractDataSource> expression;
};

class ProjectionExpression : public AbstractUnaryExpression {
public:
  ProjectionExpression(std::shared_ptr<AbstractDataSource> expression, const std::vector<std::string> &columns,
                       const std::unordered_map<std::string, std::string> &aliases,
                       const std::string &name);

  std::string toSQL() const override;

  std::vector<std::string> getHeaderVector() const override;

  std::unordered_map<std::string, size_t> getHeaderMap() const override;

  size_t getHeaderIndex(const std::string &name) const override;

  const std::string &getHeaderName(size_t index) const override;

  size_t getHeaderSize() const override;

  const std::vector<std::string> getNextRow() override;

private:
  std::unordered_map<std::string, size_t> headerMap;
  std::unordered_map<std::string, std::string> aliasToPreviousName;

  std::string getWrappedColumnName(const std::string &name) const;
};

class IntersectionExpression : public AbstractBinaryExpression {
public:
  IntersectionExpression(std::shared_ptr<AbstractDataSource> leftExpression,
                         std::shared_ptr<AbstractDataSource> rightExpression,
                         const std::string &name);

  std::string toSQL() const override;

  void reset() override;

  const std::vector<std::string> getNextRow() override;
};

class UnionExpression : public AbstractBinaryExpression {
public:
  UnionExpression(std::shared_ptr<AbstractDataSource> leftExpression,
                  std::shared_ptr<AbstractDataSource> rightExpression,
                  const std::string &name);

  std::string toSQL() const override;

  void reset() override;

  const std::vector<std::string> getNextRow() override;
};

class ExceptExpression : public AbstractBinaryExpression {
public:
  ExceptExpression(std::shared_ptr<AbstractDataSource> leftExpression,
                   std::shared_ptr<AbstractDataSource> rightExpression,
                   const std::string &name);

  std::string toSQL() const override;

  void reset() override;

  const std::vector<std::string> getNextRow() override;
};

class CartesianProductExpression : public AbstractBinaryExpression {
public:
  CartesianProductExpression(std::shared_ptr<AbstractDataSource> leftExpression,
                             std::shared_ptr<AbstractDataSource> rightExpression,
                             const std::string &name);

  std::string toSQL() const override;

  void reset() override;

  const std::vector<std::string> getNextRow() override;

  std::vector<std::string> getHeaderVector() const override;

  std::unordered_map<std::string, size_t> getHeaderMap() const override;

  size_t getHeaderIndex(const std::string &name) const override;

  const std::string &getHeaderName(size_t index) const override;

  size_t getHeaderSize() const override;

private:
  std::vector<std::string> currentLeftRow;
};

#endif //SEMESTRAL_EXPRESSIONS_H
