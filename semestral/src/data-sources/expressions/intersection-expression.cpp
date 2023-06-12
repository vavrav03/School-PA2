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
  leftExpression->reset();
  rightExpression->reset();
  nextRow = getNextRowDirectly();
}

void IntersectionExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
  nextRow = getNextRowDirectly();
}

string IntersectionExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " INTERSECT " + rightExpression->toSQL() + ") AS " + name;
}

bool IntersectionExpression::hasNextRow() const {
  return nextRow.size() > 0;
}

vector<string> IntersectionExpression::getNextRowDirectly() {
  while(leftExpression->hasNextRow()) {
    vector<string> leftRow = leftExpression->getNextRow();
    rightExpression->reset();
    while(rightExpression->hasNextRow()) {
      vector<string> rightRow = rightExpression->getNextRow();
      if (equalsVectors(leftRow, rightRow)) {
        return leftRow;
      }
    }
  }
  return vector<string>();
}

const vector<string> IntersectionExpression::getNextRow() {
  vector<string> rowToReturn = nextRow;
  nextRow = getNextRowDirectly();
  return rowToReturn;
}

