#include "./rename.h"

using namespace std;

RenameExpression::RenameExpression(AbstractDataSource *dataSource, const HeaderValueContainer &translations)
        : AbstractUnaryExpression(dataSource) {
  vector<string> newHeader;
  for (int i = 0; i < dataSource->getHeader().size(); i++) {
    if (translations.hasHeaderValue(dataSource->getHeader()[i])) {
      newHeader.push_back(translations[dataSource->getHeader()[i]]);
    } else {
      newHeader.push_back(dataSource->getHeader()[i]);
    }
  }
}

const vector<string> &RenameExpression::getHeader() const {
  return this->renamedHeader;
}

bool RenameExpression::hasNextRow() const {
  return expression->hasNextRow();
}

const vector<string> RenameExpression::getNextRow() {
  return expression->getNextRow();
}

string RenameExpression::toSQL() const {
  throw runtime_error("Not implemented");
}