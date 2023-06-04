#include "expressions.h"

using namespace std;

DataSourceExpressionWrapper::DataSourceExpressionWrapper(shared_ptr<AbstractDataSource>dataSource, const std::string &name)
        : AbstractExpression(name), expression(dataSource) {
}

/**
 * This class has atomic SQL. It just selects everything from data source it wraps by name it was given in constructor (variable name)
 * @return
 */
std::string DataSourceExpressionWrapper::toSQL() const {
  return "select * from " + name;
}

bool DataSourceExpressionWrapper::hasNextRow() const {
  return expression->hasNextRow();
}

const std::vector<std::string> DataSourceExpressionWrapper::getNextRow() {
  return expression->getNextRow();
}

void DataSourceExpressionWrapper::reset() {
  expression->reset();
}

std::vector<std::string> DataSourceExpressionWrapper::getHeaderVector() const {
  return expression->getHeaderVector();
}

std::unordered_map<std::string, int> DataSourceExpressionWrapper::getHeaderMap() const {
  return expression->getHeaderMap();
}

int DataSourceExpressionWrapper::getHeaderIndex(const std::string &name) const {
  return expression->getHeaderIndex(name);
}

const std::string &DataSourceExpressionWrapper::getHeaderName(int index) const {
  return expression->getHeaderName(index);
}

int DataSourceExpressionWrapper::getHeaderSize() const {
  return expression->getHeaderSize();
}

