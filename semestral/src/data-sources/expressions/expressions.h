#ifndef SEMESTRAL_EXPRESSIONS_H
#define SEMESTRAL_EXPRESSIONS_H

#include <string>
#include "../abstract.h"

class AbstractExpression : public AbstractDataSource {
public:
  AbstractExpression(const std::string &name) : name(name) {}

  virtual std::string toSQL() const = 0;
protected:
  std::string name;
};

class AbstractBinaryExpression : public AbstractExpression {
public:
  AbstractBinaryExpression(AbstractExpression *_left, AbstractExpression *_right, const std::string &name)
          : AbstractExpression(name), left(_left), right(_right) {}

protected:
  AbstractExpression *left;
  AbstractExpression *right;
};

class AbstractUnaryExpression : public AbstractExpression {
public:
  AbstractUnaryExpression(AbstractExpression *_expression, const std::string &name) : AbstractExpression(name),
                                                                                      expression(_expression) {}

  virtual ~AbstractUnaryExpression() {
    delete expression;
  }

protected:
  AbstractExpression *expression;
};

/**
 * This class is a wrapper for expresions that do not have direct ability to be converted to SQL. It is mostly used to
 * wrap file data sources like CSV or JSON.
 */
class DataSourceExpressionWrapper : public AbstractExpression {
public:
  DataSourceExpressionWrapper(AbstractDataSource *dataSource, const std::string &_name);
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
  AbstractDataSource *expression;
};

#endif //SEMESTRAL_EXPRESSIONS_H
