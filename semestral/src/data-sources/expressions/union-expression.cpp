#include "./expressions.h"

using namespace std;

UnionExpression::UnionExpression(shared_ptr<AbstractExpression> left,
                                 shared_ptr<AbstractExpression> right, const string &name)
        : AbstractBinaryExpression(left, right, name) {
  for (int i = 0; i < left->getHeaderSize(); i++) {
    if (left->getHeaderName(i) != right->getHeaderName(i)) {
      throw runtime_error("Cannot intersect expressions with different headers");
    }
  }
  left->reset();
  right->reset();
  nextRow = getNextRowDirectly();
}

string UnionExpression::toSQL() const {
  return "(" + left->toSQL() + " UNION " + right->toSQL() + ") AS " + name;
}

bool UnionExpression::hasNextRow() const {
  return nextRow.size() > 0;
}

void UnionExpression::reset() {
  left->reset();
  right->reset();
  nextRow = getNextRowDirectly();
}

vector<string> UnionExpression::getNextRowDirectly() {
  // first we look for all rows on left that are not on the right
  // then we just take all items from the right
  while (left->hasNextRow()) {
    bool hasMatch = false;
    vector<string> leftRow = left->getNextRow();
    printStringVector(leftRow);
    while (right->hasNextRow()) {
      vector<string> rightRow = right->getNextRow();
      if (equalsStringVectors(leftRow, rightRow)) {
        hasMatch = true;
        break;
      }
    }
    right->reset();
    if (!hasMatch) {
      return leftRow;
    }
  }
  if (right->hasNextRow()) {
    return right->getNextRow();
  }
  return vector<string>();
}

const vector<string> UnionExpression::getNextRow() {
  vector<string> rowToReturn = nextRow;
  nextRow = getNextRowDirectly();
  return rowToReturn;
}

