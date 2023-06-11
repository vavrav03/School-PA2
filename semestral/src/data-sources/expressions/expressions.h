#ifndef SEMESTRAL_EXPRESSIONS_H
#define SEMESTRAL_EXPRESSIONS_H

#include <string>
#include <iostream>
#include "../abstract.h"
#include "../../utils/utils.h"

class AbstractExpression : public AbstractDataSource {
public:
  AbstractExpression(const std::string &name) : name(name) {}

  virtual std::string toSQL() const = 0;
protected:
  std::string name;
};

class AbstractBinaryExpression : public AbstractExpression {
public:
  AbstractBinaryExpression(std::shared_ptr<AbstractExpression> left, std::shared_ptr<AbstractExpression> right,
                           const std::string &name)
          : AbstractExpression(name), left(left), right(right) {}

  void reset() override {
    left->reset();
    right->reset();
  }

  std::vector<std::string> getHeaderVector() const override {
    return left->getHeaderVector();
  }

  std::unordered_map<std::string, int> getHeaderMap() const override {
    return left->getHeaderMap();
  }

  int getHeaderIndex(const std::string &name) const override {
    return left->getHeaderIndex(name);
  }

  const std::string &getHeaderName(int index) const override {
    return left->getHeaderName(index);
  }

  int getHeaderSize() const override {
    return left->getHeaderSize();
  }

protected:
  std::shared_ptr<AbstractExpression> left;
  std::shared_ptr<AbstractExpression> right;
};

class AbstractUnaryExpression : public AbstractExpression {
public:
  AbstractUnaryExpression(std::shared_ptr<AbstractExpression> expression, const std::string &name) : AbstractExpression(
          name),
                                                                                                     expression(
                                                                                                             expression) {}

  void reset() override {
    expression->reset();
  }

  bool hasNextRow() const override {
    return expression->hasNextRow();
  }

  const std::vector<std::string> getNextRow() override {
    return expression->getNextRow();
  }

  std::vector<std::string> getHeaderVector() const override {
    return expression->getHeaderVector();
  }

  std::unordered_map<std::string, int> getHeaderMap() const override {
    return expression->getHeaderMap();
  }

  int getHeaderIndex(const std::string &name) const override {
    return expression->getHeaderIndex(name);
  }

  const std::string &getHeaderName(int index) const override {
    return expression->getHeaderName(index);
  }

  int getHeaderSize() const override {
    return expression->getHeaderSize();
  }

protected:
  std::shared_ptr<AbstractExpression> expression;
};

/**
 * This class is a wrapper for expressions that do not have direct ability to be converted to SQL. It is mostly used to
 * wrap file data sources like CSV or JSON.
 */
class DataSourceExpressionWrapper : public AbstractExpression {
public:
  DataSourceExpressionWrapper(std::shared_ptr<AbstractDataSource> dataSource, const std::string &name);
  std::string toSQL() const override;
  virtual std::vector<std::string> getHeaderVector() const override;
  virtual std::unordered_map<std::string, int> getHeaderMap() const override;
  virtual int getHeaderIndex(const std::string &name) const override;
  virtual const std::string &getHeaderName(int index) const override;
  virtual int getHeaderSize() const override;
  virtual void reset() override;
  virtual bool hasNextRow() const override;
  virtual const std::vector<std::string> getNextRow() override;
private:
  std::shared_ptr<AbstractDataSource> expression;
};

class ProjectionExpression : public AbstractUnaryExpression {
public:
  ProjectionExpression(std::shared_ptr<AbstractExpression> expression, const std::vector<std::string> &columns,
                       const std::unordered_map<std::string, std::string> &aliases,
                       const std::string &name);

  std::string toSQL() const override;
  std::vector<std::string> getHeaderVector() const override;
  std::unordered_map<std::string, int> getHeaderMap() const override;
  int getHeaderIndex(const std::string &name) const override;
  const std::string &getHeaderName(int index) const override;
  int getHeaderSize() const override;
  const std::vector<std::string> getNextRow() override;
private:
  std::unordered_map<std::string, int> headerMap;
  std::unordered_map<std::string, std::string> aliasToPreviousName;
  std::string getWrappedColumnName(const std::string &name) const;
};

class IntersectionExpression: public AbstractBinaryExpression {
public:
  IntersectionExpression(std::shared_ptr<AbstractExpression> left, std::shared_ptr<AbstractExpression> right,
                         const std::string &name);

  std::string toSQL() const override;
  const std::vector<std::string> getNextRow() override;
  bool hasNextRow() const override;
private:
  std::vector<std::string> nextRow;
  std::vector<std::string> getNextRowDirectly();
};

#endif //SEMESTRAL_EXPRESSIONS_H
