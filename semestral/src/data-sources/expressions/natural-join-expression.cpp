#include "./expressions.h"

using namespace std;

NaturalJoinExpression::NaturalJoinExpression(std::unique_ptr<AbstractDataSource> left,
                                             std::unique_ptr<AbstractDataSource> right,
                                             const std::string &name) : AbstractBinaryExpression(std::move(left),
                                                                                                 std::move(right),
                                                                                                 name) {
  sameColumns = getSameKeys(leftExpression->getHeaderMap(), rightExpression->getHeaderMap());
  headerMap = joinIndexMaps(leftExpression->getHeaderMap(), rightExpression->getHeaderMap());
  currentLeftRow = leftExpression->getNextRow();
}

string NaturalJoinExpression::toSQL() const {
  return "(" + leftExpression->toSQL() + " NATURAL JOIN " + rightExpression->toSQL() + ") AS " + name;
}

void NaturalJoinExpression::reset() {
  leftExpression->reset();
  rightExpression->reset();
  currentLeftRow = leftExpression->getNextRow();
}

const vector<string> NaturalJoinExpression::getNextRow() {
  while (true) {
    vector<string> rightRow = rightExpression->getNextRow();
    if (rightRow.empty()) {
      rightExpression->reset();
      rightRow = rightExpression->getNextRow();
      currentLeftRow = leftExpression->getNextRow();
    }
    if (currentLeftRow.empty()) {
      return vector<string>();
    }
    bool allMatch = true;
    for (const auto &key : sameColumns) {
      if (currentLeftRow[leftExpression->getHeaderIndex(key)] != rightRow[rightExpression->getHeaderIndex(key)]) {
        allMatch = false;
        continue;
      }
    }
    if (!allMatch) {
      continue;
    }
    vector<string> result(this->getHeaderSize());
    for (auto &key : this->getHeaderMap()) {
      result[this->getHeaderIndex(key.first)] =
          leftExpression->getHeaderMap().count(key.first)
          ? currentLeftRow[leftExpression->getHeaderIndex(key.first)]
          : rightRow[rightExpression->getHeaderIndex(key.first)];
    }
    return result;
  }
}

vector<string> NaturalJoinExpression::getHeaderVector() const {
  return indexMapToVector(headerMap);
}

unordered_map<string, size_t> NaturalJoinExpression::getHeaderMap() const {
  return headerMap;
}

size_t NaturalJoinExpression::getHeaderIndex(const string &name) const {
  return headerMap.at(name);
}

const string &NaturalJoinExpression::getHeaderName(size_t index) const {
  return findValueOrThrowInIndexMap(headerMap, index);
}

size_t NaturalJoinExpression::getHeaderSize() const {
  return headerMap.size();
}

unique_ptr<AbstractDataSource> NaturalJoinExpression::clone() const {
  return make_unique<NaturalJoinExpression>(leftExpression->clone(), rightExpression->clone(), name);
}
