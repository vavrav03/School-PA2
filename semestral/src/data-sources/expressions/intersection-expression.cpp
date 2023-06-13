#include "./expressions.h"

using namespace std;

IntersectionExpression::IntersectionExpression(shared_ptr<AbstractExpression> left,
                                               shared_ptr<AbstractExpression> right, const string &name)
        : AbstractBinaryExpression(left, right, name) {
  for (size_t i = 0; i < leftExpression->getHeaderSize(); i++) {
    if (leftExpression->getHeaderName(i) != rightExpression->getHeaderName(i)) {
      throw runtime_error("Cannot intersect expressions with different headers");
    }
  }
}

void IntersectionExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
}

string IntersectionExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " INTERSECT " + rightExpression->toSQL() + ") AS " + name;
}

const vector<string> IntersectionExpression::getNextRow() {
  vector<string> leftRow;
  while (!(leftRow = leftExpression->getNextRow()).empty()) {
    vector<string> rightRow;
    rightExpression->reset();
    while (!(rightRow = rightExpression->getNextRow()).empty()) {
      if (equalsVectors(leftRow, rightRow)) {
        return leftRow;
      }
    }
  }
  return vector<string>();
}
