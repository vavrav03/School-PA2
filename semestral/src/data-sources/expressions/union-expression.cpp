#include "./expressions.h"

using namespace std;

UnionExpression::UnionExpression(shared_ptr<AbstractExpression> left,
                                 shared_ptr<AbstractExpression> right, const string &name)
        : AbstractBinaryExpression(left, right, name) {
  for (size_t i = 0; i < leftExpression->getHeaderSize(); i++) {
    if (leftExpression->getHeaderName(i) != rightExpression->getHeaderName(i)) {
      throw runtime_error("Cannot intersect expressions with different headers");
    }
  }
  leftExpression->reset();
  rightExpression->reset();
  nextRow = getNextRowDirectly();
}

string UnionExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " UNION " + rightExpression->toSQL() + ") AS " + name;
}

bool UnionExpression::hasNextRow() const {
  return nextRow.size() > 0;
}

void UnionExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
  nextRow = getNextRowDirectly();
}

vector<string> UnionExpression::getNextRowDirectly() {
  // first we look for all rows on left that are not on the right
  // then we just take all items from the right
  while (leftExpression->hasNextRow()) {
    bool hasMatch = false;
    vector<string> leftRow = leftExpression->getNextRow();
    while (rightExpression->hasNextRow()) {
      vector<string> rightRow = rightExpression->getNextRow();
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
  if (rightExpression->hasNextRow()) {
    return rightExpression->getNextRow();
  }
  return vector<string>();
}

const vector<string> UnionExpression::getNextRow() {
  vector<string> rowToReturn = nextRow;
  nextRow = getNextRowDirectly();
  return rowToReturn;
}

