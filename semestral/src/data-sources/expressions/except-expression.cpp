#include "./expressions.h"

using namespace std;

ExceptExpression::ExceptExpression(shared_ptr<AbstractDataSource> left,
                                   shared_ptr<AbstractDataSource> right, const string &name)
    : AbstractBinaryExpression(left, right, name) {
  for (size_t i = 0; i < leftExpression->getHeaderSize(); i++) {
    if (leftExpression->getHeaderName(i) != rightExpression->getHeaderName(i)) {
      throw runtime_error("Cannot intersect expressions with different headers");
    }
  }
}

string ExceptExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " EXCEPT " + rightExpression->toSQL() + ") AS " + name;
}

void ExceptExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
}

const vector<string> ExceptExpression::getNextRow() {
  vector<string> leftRow;
  while (!(leftRow = leftExpression->getNextRow()).empty()) {
    bool hasMatch = false;
    vector<string> rightRow;
    rightExpression->reset();
    while (!(rightRow = rightExpression->getNextRow()).empty()) {
      if (equalsVectors(leftRow, rightRow)) {
        hasMatch = true;
        break;
      }
    }
    if (!hasMatch) {
      return leftRow;
    }
  }
  return vector<string>();
}
