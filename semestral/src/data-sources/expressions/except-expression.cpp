#include "./expressions.h"

using namespace std;

ExceptExpression::ExceptExpression(shared_ptr<AbstractExpression> left,
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

string ExceptExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " EXCEPT " + rightExpression->toSQL() + ") AS " + name;
}

bool ExceptExpression::hasNextRow() const {
  return nextRow.size() > 0;
}

void ExceptExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
  nextRow = getNextRowDirectly();
}

vector<string> ExceptExpression::getNextRowDirectly() {
  while (leftExpression->hasNextRow()) {
    bool hasMatch = false;
    vector<string> leftRow = leftExpression->getNextRow();
    rightExpression->reset();
    while (rightExpression->hasNextRow()) {
      vector<string> rightRow = rightExpression->getNextRow();
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

const vector<string> ExceptExpression::getNextRow() {
  vector<string> rowToReturn = nextRow;
  nextRow = getNextRowDirectly();
  return rowToReturn;
}