#ifndef SEMESTRAL_EXPRESSIONS_H
#define SEMESTRAL_EXPRESSIONS_H

#include <string>
#include "../abstract.h"

class AbstractExpression : public AbstractDataSource
{
public:
  AbstractExpression() = default;
  virtual std::string toSQL() const = 0;
};

class AbstractBinaryExpression : public AbstractExpression
{
public:
  AbstractBinaryExpression(AbstractExpression *_left, AbstractExpression *_right)
      : left(_left), right(_right) {}

protected:
  AbstractExpression *left;
  AbstractExpression *right;
};

class AbstractUnaryExpression : public AbstractExpression {
public:
  AbstractUnaryExpression(AbstractDataSource *_expression)
          : expression(_expression) {}

  virtual ~AbstractUnaryExpression() {
    delete expression;
  }

protected:
  AbstractDataSource *expression;
};

class NamedDataSourceExpression : public AbstractUnaryExpression {
public:
  NamedDataSourceExpression(AbstractDataSource * dataSource, const std::string &_name);
  std::string toSQL() const override;
  virtual std::vector<std::string> getHeaderVector() const override;
  virtual std::unordered_map<std::string, int> getHeaderMap() const override;
  virtual int getHeaderIndex(const std::string &name) const override;
  virtual const std::string& getHeaderName(int index) const override;
  virtual int getHeaderSize() const override;
  virtual void reset() override;
  virtual bool hasNextRow() const override;
  virtual const std::vector<std::string> getNextRow() override;

private:
  std::string name;
};

#endif //SEMESTRAL_EXPRESSIONS_H
