#include "./expressions.h"

using namespace std;

UnionExpression::UnionExpression(shared_ptr<AbstractDataSource> left,
                                 shared_ptr<AbstractDataSource> right, const string &name)
        : AbstractBinaryExpression(left, right, name) {
  for (size_t i = 0; i < leftExpression->getHeaderSize(); i++) {
    if (leftExpression->getHeaderName(i) != rightExpression->getHeaderName(i)) {
      throw runtime_error("Cannot intersect expressions with different headers");
    }
  }
}

string UnionExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " UNION " + rightExpression->toSQL() + ") AS " + name;
}

void UnionExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
}

const vector<string> UnionExpression::getNextRow() {
  // first we look for all rows on left that are not on the right
  // then we just take all items from the right
  vector<string> leftRow;
  while (!(leftRow = leftExpression->getNextRow()).empty()) {
    bool hasMatch = false;
    vector<string> rightRow;
    while (!(rightRow = rightExpression->getNextRow()).empty()) {
      if (equalsVectors(leftRow, rightRow)) {
        hasMatch = true;
        break;
      }
    }
    rightExpression->reset();
    if (!hasMatch) {
      return leftRow;
    }
  }
  return rightExpression->getNextRow(); // if nothing is there, it will return an empty vector
}
