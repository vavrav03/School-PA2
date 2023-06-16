#include "./expressions.h"

using namespace std;

IntersectionExpression::IntersectionExpression(unique_ptr<AbstractDataSource> left,
                                               unique_ptr<AbstractDataSource> right)
        : AbstractBinaryExpression(std::move(left), std::move(right)) {
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
  return "SELECT * FROM (" + leftExpression->toSQL() + " INTERSECT " + rightExpression->toSQL() + ")";
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

unique_ptr<AbstractDataSource> IntersectionExpression::clone() const {
  return make_unique<IntersectionExpression>(leftExpression->clone(), rightExpression->clone());
}
