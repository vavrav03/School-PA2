#include "./expressions.h"

using namespace std;

ExceptExpression::ExceptExpression(shared_ptr<AbstractExpression> left,
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

string ExceptExpression::toSQL() const {
  return "(" + left->toSQL() + " EXCEPT " + right->toSQL() + ") AS " + name;
}

bool ExceptExpression::hasNextRow() const {
  return nextRow.size() > 0;
}

void ExceptExpression::reset() {
  left->reset();
  right->reset();
  nextRow = getNextRowDirectly();
}

vector<string> ExceptExpression::getNextRowDirectly() {
  while (left->hasNextRow()) {
    bool hasMatch = false;
    vector<string> leftRow = left->getNextRow();
    right->reset();
    while (right->hasNextRow()) {
      vector<string> rightRow = right->getNextRow();
      if (equalsStringVectors(leftRow, rightRow)) {
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