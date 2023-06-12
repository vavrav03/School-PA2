#include "./expressions.h"

using namespace std;

CartesianProductExpression::CartesianProductExpression(std::shared_ptr<AbstractExpression> left,
                                                       std::shared_ptr<AbstractExpression> right,
                                                       const std::string &name) : AbstractBinaryExpression(left, right,
                                                                                                           name) {
  leftExpression->reset();
  rightExpression->reset();
  if(!leftExpression->hasNextRow()) {
    throw runtime_error("Cannot perform cartesian product on empty left expression");
  }
  if(!rightExpression->hasNextRow()) {
    throw runtime_error("Cannot perform cartesian product on empty right expression");
  }
  if(mapsContainSameKey(leftExpression->getHeaderMap(), rightExpression->getHeaderMap())) {
    throw runtime_error("Cannot perform cartesian product on expressions with same column names");
  }
  currentLeftRow = leftExpression->getNextRow();
}

string CartesianProductExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " CROSS JOIN " + rightExpression->toSQL() + ") AS " + name;
}

bool CartesianProductExpression::hasNextRow() const {
  return leftExpression->hasNextRow() || rightExpression->hasNextRow();
}

void CartesianProductExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
  currentLeftRow = leftExpression->getNextRow();
}

const vector<string> CartesianProductExpression::getNextRow() {
  if(!rightExpression->hasNextRow()) {
    rightExpression->reset();
    if(!leftExpression->hasNextRow()) {
      throw runtime_error("No more rows in cartesian product expression");
    }
    currentLeftRow = leftExpression->getNextRow();
  }
  vector<string> rightRow = rightExpression->getNextRow();
  return joinVectors(currentLeftRow, rightRow);
}

vector<string> CartesianProductExpression::getHeaderVector() const {
  return joinVectors(leftExpression->getHeaderVector(), rightExpression->getHeaderVector());
}

size_t CartesianProductExpression::getHeaderSize() const {
  return leftExpression->getHeaderSize() + rightExpression->getHeaderSize();
}

unordered_map<string, size_t> CartesianProductExpression::getHeaderMap() const {
  unordered_map<string, size_t> headerMap = leftExpression->getHeaderMap();
  unordered_map<string, size_t> rightHeaderMap = rightExpression->getHeaderMap();
  for (auto &pair: rightHeaderMap) {
    headerMap[pair.first] = pair.second + leftExpression->getHeaderSize();
  }
  return headerMap;
}

const string &CartesianProductExpression::getHeaderName(size_t index) const {
  if (index < leftExpression->getHeaderSize()) {
    return leftExpression->getHeaderName(index);
  } else {
    return rightExpression->getHeaderName(index - leftExpression->getHeaderSize());
  }
}

size_t CartesianProductExpression::getHeaderIndex(const string &name) const {
  if (leftExpression->getHeaderMap().count(name) > 0) {
    return leftExpression->getHeaderMap().at(name);
  } else {
    return rightExpression->getHeaderMap().at(name) + leftExpression->getHeaderSize();
  }
}