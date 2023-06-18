#include "./expressions.h"

using namespace std;

ThetaJoinExpression::ThetaJoinExpression(std::unique_ptr<AbstractDataSource> left,
                     std::unique_ptr<AbstractDataSource> right,
                     std::unique_ptr<AbstractBooleanExpression> condition)
    : CartesianProductExpression(std::move(left), std::move(right)), condition(std::move(condition)) {
}

string ThetaJoinExpression::toSQL() const {
  return "SELECT * FROM (" + leftExpression->toSQL() + " JOIN " + rightExpression->toSQL() + " ON ("
      + condition->toSQL() + "))";
}

const vector<string> ThetaJoinExpression::getNextRow() {
  while (true) {
    vector<string> rightRow = rightExpression->getNextRow();
    if (rightRow.empty()) {
      rightExpression->reset();
      rightRow = rightExpression->getNextRow();
      currentLeftRow = leftExpression->getNextRow();
      if (currentLeftRow.empty()) {
        return vector<string>();
      }
    }
    vector<string> probableResult = joinVectors(currentLeftRow, rightRow);
    if (condition->evaluate(HeaderRowMapping(probableResult, this->getHeaderMap()))) {
      return probableResult;
    }
  }
}

unique_ptr<AbstractDataSource> ThetaJoinExpression::clone() const {
  return make_unique<ThetaJoinExpression>(leftExpression->clone(), rightExpression->clone(), condition->clone());
}

