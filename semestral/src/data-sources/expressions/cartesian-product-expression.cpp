#include "./expressions.h"

using namespace std;

CartesianProductExpression::CartesianProductExpression(std::shared_ptr<AbstractExpression> left,
                                                       std::shared_ptr<AbstractExpression> right,
                                                       const std::string &name) : AbstractBinaryExpression(left, right,
                                                                                                           name) {
  left->reset();
  right->reset();
  if(!left->hasNextRow()) {
    throw runtime_error("Cannot perform cartesian product on empty left expression");
  }
  if(!right->hasNextRow()) {
    throw runtime_error("Cannot perform cartesian product on empty right expression");
  }
  if(mapsContainSameKey(left->getHeaderMap(), right->getHeaderMap())) {
    throw runtime_error("Cannot perform cartesian product on expressions with same column names");
  }
  currentLeftRow = left->getNextRow();
}

string CartesianProductExpression::toSQL() const {
  return "(" + left->toSQL() + " CROSS JOIN " + right->toSQL() + ") AS " + name;
}

bool CartesianProductExpression::hasNextRow() const {
  return left->hasNextRow() || right->hasNextRow();
}

void CartesianProductExpression::reset() {
  left->reset();
  right->reset();
  currentLeftRow = left->getNextRow();
}

const vector<string> CartesianProductExpression::getNextRow() {
  if(!right->hasNextRow()) {
    right->reset();
    if(!left->hasNextRow()) {
      throw runtime_error("No more rows in cartesian product expression");
    }
    currentLeftRow = left->getNextRow();
  }
  vector<string> rightRow = right->getNextRow();
  return joinStringVectors(currentLeftRow, rightRow);
}

vector<string> CartesianProductExpression::getHeaderVector() const {
  return joinStringVectors(left->getHeaderVector(), right->getHeaderVector());
}

int CartesianProductExpression::getHeaderSize() const {
  return left->getHeaderSize() + right->getHeaderSize();
}

unordered_map<string, int> CartesianProductExpression::getHeaderMap() const {
  unordered_map<string, int> headerMap = left->getHeaderMap();
  unordered_map<string, int> rightHeaderMap = right->getHeaderMap();
  for (auto &pair: rightHeaderMap) {
    headerMap[pair.first] = pair.second + left->getHeaderSize();
  }
  return headerMap;
}

const string &CartesianProductExpression::getHeaderName(int index) const {
  if (index < left->getHeaderSize()) {
    return left->getHeaderName(index);
  } else {
    return right->getHeaderName(index - left->getHeaderSize());
  }
}

int CartesianProductExpression::getHeaderIndex(const string &name) const {
  if (left->getHeaderMap().count(name) > 0) {
    return left->getHeaderMap().at(name);
  } else {
    return right->getHeaderMap().at(name) + left->getHeaderSize();
  }
}