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

IntersectionOperator::IntersectionOperator(): OperationPart(OperationPartType::BINARY_OPERATOR, 1) {}

void
IntersectionOperator::evaluate(std::stack<std::shared_ptr<AbstractExpression> > &parts, std::string &operationAlias) {
  auto right = parts.top();
  parts.pop();
  auto left = parts.top();
  parts.pop();
  return parts.push(make_shared<IntersectionExpression>(left, right, operationAlias));
}
