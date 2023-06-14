#include "./expressions.h"

using namespace std;

CartesianProductExpression::CartesianProductExpression(std::unique_ptr<AbstractDataSource> left,
                                                       std::unique_ptr<AbstractDataSource> right,
                                                       const std::string &name) : AbstractBinaryExpression(std::move(left), std::move(right),
                                                                                                           name) {
  if (mapsContainSameKey(leftExpression->getHeaderMap(), rightExpression->getHeaderMap())) {
    throw runtime_error("Cannot perform cartesian product on expressions with same column names");
  }
  currentLeftRow = leftExpression->getNextRow();
}

string CartesianProductExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " CROSS JOIN " + rightExpression->toSQL() + ") AS " + name;
}

void CartesianProductExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
  currentLeftRow = leftExpression->getNextRow();
}

const vector<string> CartesianProductExpression::getNextRow() {
  vector<string> rightRow = rightExpression->getNextRow();
  if (rightRow.empty()) {
    rightExpression->reset();
    rightRow = rightExpression->getNextRow();
    currentLeftRow = leftExpression->getNextRow();
    if (currentLeftRow.empty()) {
      return vector<string>();
    }
  }
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
  for (auto &pair : rightHeaderMap) {
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

unique_ptr<AbstractDataSource> CartesianProductExpression::clone() const {
  return make_unique<CartesianProductExpression>(leftExpression->clone(), rightExpression->clone(), name);
}
