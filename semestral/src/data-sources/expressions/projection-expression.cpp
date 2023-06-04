#include "./expressions.h"

using namespace std;

ProjectionExpression::ProjectionExpression(shared_ptr<AbstractExpression> expression, const std::vector<std::string> &columns,
                       const std::string &name) : AbstractUnaryExpression(expression, name) {
  vector<int> indexes(expression->getHeaderSize());
  for(const std::string &column : columns) {
    // it throws if column does not exist
    indexes[expression->getHeaderIndex(column)]++;
  }
  for(int i = 0; i < indexes.size(); i++) {
    if(indexes[i] > 1) {
      throw runtime_error("Column " + expression->getHeaderName(i) + " is duplicated");
    }
  }
  this->headerMap = vectorToIndexMap(columns);
}

string ProjectionExpression::toSQL() const {
  return "SELECT " + join(this->getHeaderVector(), ",") + " FROM (" + this->expression->toSQL() + ") AS " + this->name;
}

vector<string> ProjectionExpression::getHeaderVector() const {
  return indexMapToVector(this->headerMap);
}

unordered_map<string, int> ProjectionExpression::getHeaderMap() const {
  return this->headerMap;
}

int ProjectionExpression::getHeaderIndex(const string &name) const {
  return this->headerMap.at(name);
}

const string & ProjectionExpression::getHeaderName(int index) const {
  for(auto &pair: this->headerMap) {
    if(pair.second == index) {
      return pair.first;
    }
  }
  throw runtime_error("Index not found");
}

int ProjectionExpression::getHeaderSize() const {
  return this->headerMap.size();
}

const vector<string> ProjectionExpression::getNextRow() {
  vector<string> header = this->getHeaderVector();
  vector<string> row(header.size());
  vector<string> nextRow = this->expression->getNextRow();
  for(int i = 0; i < header.size(); i++) {
    row[i] = nextRow[this->expression->getHeaderIndex(header[i])];
  }
  return row;
}

