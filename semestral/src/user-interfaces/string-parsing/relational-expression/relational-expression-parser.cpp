#include "relational-expression-parser.h"
#include <iostream>
using namespace std;

RelationalExpressionParser::RelationalExpressionParser(vector<shared_ptr<OperationPartFactory> > &factories)
        : factories(factories) {}

RelationalExpressionParser
RelationalExpressionParser::createDefaultInstance(const Tokenizer &tokenizer, VariablesMemory &memory) {
  vector<shared_ptr<OperationPartFactory> > factories;
  factories.push_back(make_shared<LeftBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_shared<RightBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_shared<ProjectionOperatorFactory>(tokenizer));
  factories.push_back(make_shared<DataSourceExpressionOperationPartFactory>(tokenizer, memory));
  return RelationalExpressionParser(factories);
}

shared_ptr<AbstractExpression> RelationalExpressionParser::createExpressionFromTokens(
        const std::vector<Token> &tokens) const {
  vector<OperationPart*> infix = createInfixFromTokens(tokens);
  return createExpressionFromPostfix(infix);
}

vector<OperationPart*> RelationalExpressionParser::createInfixFromTokens(const vector<Token> &tokens) const {
  int nextTokenIndex = 0;
  vector<OperationPart *> infix;
  while (nextTokenIndex < tokens.size()) {
    bool found = false;
    for (auto factory: factories) {
      if (factory->canCreate(tokens, nextTokenIndex)) {
        infix.push_back(factory->create(tokens, nextTokenIndex));
        found = true;
        break;
      }
    }

    if (!found) {
      throw runtime_error("Unknown token " + tokens[nextTokenIndex].value);
    }
  }
  return infix;
}

string RelationalExpressionParser::getNextAlias(string lastAlias) const {
  if (lastAlias.empty()) {
    return "a";
  }
  if (lastAlias.back() == 'z') {
    return lastAlias + "a";
  }
  return lastAlias.substr(0, lastAlias.size() - 1) + (char) (lastAlias.back() + 1);
}

shared_ptr<AbstractExpression> RelationalExpressionParser::createExpressionFromPostfix(
        const std::vector<OperationPart*> &parts) const {
  stack<shared_ptr<AbstractExpression> > expressions;
  string lastAlias;
  string currentAlias;
  for (auto part: parts) {
    currentAlias = getNextAlias(lastAlias);
    lastAlias = currentAlias;
    part->evaluate(expressions, currentAlias);
    delete part;
  }
  return expressions.top();
}
