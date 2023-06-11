#include "./expression-operation-part.h"

using namespace std;

IntersectionOperatorFactory::IntersectionOperatorFactory(const Tokenizer &tokenizer) : OperationPartFactory(tokenizer) {}

bool IntersectionOperatorFactory::canCreate(const vector<Token> &tokens, int nextTokenIndex) const {
  return tokens[nextTokenIndex].value == "∩";
}

OperationPart* IntersectionOperatorFactory::create(const vector<Token> &tokens, int& nextTokenIndex) const {
  nextTokenIndex++;
  return new IntersectionOperator();
}

IntersectionOperator::IntersectionOperator(): OperationPart(OperationPartType::BINARY_OPERATOR, 9) {}

void
IntersectionOperator::evaluate(std::stack<std::shared_ptr<AbstractExpression> > &parts, std::string &operationAlias) {
  auto right = parts.top();
  parts.pop();
  auto left = parts.top();
  parts.pop();
  return parts.push(make_shared<IntersectionExpression>(left, right, operationAlias));
}


UnionOperatorFactory::UnionOperatorFactory(const Tokenizer &tokenizer) : OperationPartFactory(tokenizer) {}

bool UnionOperatorFactory::canCreate(const vector<Token> &tokens, int nextTokenIndex) const {
  return tokens[nextTokenIndex].value == "∪";
}

OperationPart* UnionOperatorFactory::create(const vector<Token> &tokens, int& nextTokenIndex) const {
  nextTokenIndex++;
  return new UnionOperator();
}

UnionOperator::UnionOperator(): OperationPart(OperationPartType::BINARY_OPERATOR, 10) {}

void UnionOperator::evaluate(std::stack<std::shared_ptr<AbstractExpression> > &parts, std::string &operationAlias) {
  auto right = parts.top();
  parts.pop();
  auto left = parts.top();
  parts.pop();
  return parts.push(make_shared<UnionExpression>(left, right, operationAlias));
}

ExceptOperatorFactory::ExceptOperatorFactory(const Tokenizer &tokenizer) : OperationPartFactory(tokenizer) {}

bool ExceptOperatorFactory::canCreate(const vector<Token> &tokens, int nextTokenIndex) const {
  return tokens[nextTokenIndex].value == "\\";
}

OperationPart* ExceptOperatorFactory::create(const vector<Token> &tokens, int& nextTokenIndex) const {
  nextTokenIndex++;
  return new ExceptOperator();
}

ExceptOperator::ExceptOperator(): OperationPart(OperationPartType::BINARY_OPERATOR, 10) {}

void ExceptOperator::evaluate(std::stack<std::shared_ptr<AbstractExpression> > &parts, std::string &operationAlias) {
  auto right = parts.top();
  parts.pop();
  auto left = parts.top();
  parts.pop();
  return parts.push(make_shared<ExceptExpression>(left, right, operationAlias));
}
