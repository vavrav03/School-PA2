#include "expressions.h"

NamedDataSourceExpression::NamedDataSourceExpression(AbstractDataSource *dataSource, const std::string &_name)
        : AbstractUnaryExpression(dataSource), name(_name) {
}

std::string NamedDataSourceExpression::toSQL() const {
  return "select * from " + name;
}

bool NamedDataSourceExpression::hasNextRow() const {
  return expression->hasNextRow();
}

const std::vector<std::string> NamedDataSourceExpression::getNextRow() {
  return expression->getNextRow();
}

void NamedDataSourceExpression::reset() {
  expression->reset();
}

std::vector<std::string> NamedDataSourceExpression::getHeaderVector() const {
  return expression->getHeaderVector();
}

std::unordered_map<std::string, int> NamedDataSourceExpression::getHeaderMap() const {
  return expression->getHeaderMap();
}

int NamedDataSourceExpression::getHeaderIndex(const std::string &name) const {
  return expression->getHeaderIndex(name);
}

const std::string &NamedDataSourceExpression::getHeaderName(int index) const {
  return expression->getHeaderName(index);
}

int NamedDataSourceExpression::getHeaderSize() const {
  return expression->getHeaderSize();
}

