#include "./expressions.h"

using namespace std;

SelectionExpression::SelectionExpression(unique_ptr<AbstractDataSource> expression,
                                         unique_ptr<AbstractBooleanExpression> condition)
    : AbstractUnaryExpression(move(expression)), condition(std::move(condition)) {}

string SelectionExpression::toSQL() const {
  return "SELECT * FROM " + expression->toSQL() + " WHERE " + condition->toSQL();
}

unique_ptr<AbstractDataSource> SelectionExpression::clone() const {
  return make_unique<SelectionExpression>(expression->clone(), condition->clone());
}

const vector<string> SelectionExpression::getNextRow() {
  vector<string> row;
  while (true) {
    row = expression->getNextRow();
    if (row.empty()) {
      return row;
    }
    if (condition->evaluate(HeaderRowMapping(row, expression->getHeaderMap()))) {
      return row;
    }
  }
}
