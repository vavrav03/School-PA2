#include "./expressions.h"

using namespace std;

IntersectionExpression::IntersectionExpression(shared_ptr<AbstractExpression> left,
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

void IntersectionExpression::reset() {
  left->reset();
  right->reset();
  nextRow = getNextRowDirectly();
}

string IntersectionExpression::toSQL() const {
  return "(" + left->toSQL() + " INTERSECT " + right->toSQL() + ") AS " + name;
}

bool IntersectionExpression::hasNextRow() const {
  return nextRow.size() > 0;
}

vector<string> IntersectionExpression::getNextRowDirectly() {
  while(left->hasNextRow()) {
    vector<string> leftRow = left->getNextRow();
    right->reset();
    while(right->hasNextRow()) {
      vector<string> rightRow = right->getNextRow();
      if (equalsStringVectors(leftRow, rightRow)) {
        printStringVector(leftRow);
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

