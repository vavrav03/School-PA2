#include "./expressions.h"

using namespace std;

ProjectionExpression::ProjectionExpression(shared_ptr<AbstractDataSource> expression,
                                           const std::vector<std::string> &columns,
                                           const unordered_map<string, string> &aliasToPreviousName,
                                           const std::string &name) : AbstractUnaryExpression(expression, name) {
  vector<int> indexes(expression->getHeaderSize());
  this->aliasToPreviousName = aliasToPreviousName;
  for (const std::string &column: columns) {
    indexes[expression->getHeaderIndex(getWrappedColumnName(column))]++;
  }
  for (size_t i = 0; i < indexes.size(); i++) {
    if (indexes[i] > 1) {
      throw runtime_error("Column " + expression->getHeaderName(i) + " is duplicated");
    }
  }
  this->headerMap = vectorToIndexMap(columns);
}

string ProjectionExpression::toSQL() const {
  string sql = "SELECT ";
  vector<string> header = this->getHeaderVector();
  for (size_t i = 0; i < header.size(); i++) {
    if (i > 0) {
      sql += ", ";
    }
    if (aliasToPreviousName.count(header[i]) > 0) {
      sql += aliasToPreviousName.at(header[i]) + " AS " + header[i];
    } else {
      sql += header[i];
    }
  }
  sql += " FROM (" + this->expression->toSQL() + ") AS " + this->name;
  return sql;
}

vector<string> ProjectionExpression::getHeaderVector() const {
  return indexMapToVector(this->headerMap);
}

unordered_map<string, size_t> ProjectionExpression::getHeaderMap() const {
  return this->headerMap;
}

size_t ProjectionExpression::getHeaderIndex(const string &name) const {
  return this->headerMap.at(name);
}

const string &ProjectionExpression::getHeaderName(size_t index) const {
  for (auto &pair: this->headerMap) {
    if (pair.second == index) {
      return pair.first;
    }
  }
  throw runtime_error("Index not found");
}

size_t ProjectionExpression::getHeaderSize() const {
  return this->headerMap.size();
}

const vector<string> ProjectionExpression::getNextRow() {
  vector<string> header = this->getHeaderVector();
  vector<string> row(header.size());
  vector<string> nextRow = this->expression->getNextRow();
  if(nextRow.empty()) {
    return vector<string>();
  }
  for (size_t i = 0; i < header.size(); i++) {
    row[i] = nextRow[this->expression->getHeaderIndex(getWrappedColumnName(header[i]))];
  }
  return row;
}

std::string ProjectionExpression::getWrappedColumnName(const std::string &name) const {
  if (this->aliasToPreviousName.count(name) > 0) {
    return this->aliasToPreviousName.at(name);
  } else {
    return name;
  }
}