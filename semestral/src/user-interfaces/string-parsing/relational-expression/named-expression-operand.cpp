#include "./expression-operation-part.h"

using namespace std;

DataSourceExpressionOperationPartFactory::DataSourceExpressionOperationPartFactory(const Tokenizer &tokenizer,
                                                                                   VariablesMemory &memory)
        : OperationPartFactory(tokenizer), memory(memory) {}

bool DataSourceExpressionOperationPartFactory::canCreate(const vector<Token> &tokens, int nextTokenIndex) const {
  if (tokens[nextTokenIndex].quoted) {
    return true;
  }
  return !tokenizer.isSpecialCharacter(tokens[nextTokenIndex].value);
}

OperationPart *
DataSourceExpressionOperationPartFactory::create(const vector<Token> &tokens, int &nextTokenIndex) const {
  OperationPart * returnValue = new DataSourceExpressionOperationPart(memory.get(tokens[nextTokenIndex].value));
  nextTokenIndex++;
  return returnValue;
}

DataSourceExpressionOperationPart::DataSourceExpressionOperationPart(const shared_ptr<AbstractExpression> &expression)
        : OperationPart(OperationPartType::OPERAND, 1999), expression(expression) {}

void
DataSourceExpressionOperationPart::evaluate(stack<shared_ptr<AbstractExpression> > &parts, string &operationAlias) {
  parts.push(expression);
}