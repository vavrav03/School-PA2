#include "relational-expression-parser.h"

using namespace std;

RelationalExpressionParser::RelationalExpressionParser(vector<shared_ptr<OperationPartFactory> > &factories, VariablesMemory &memory)
        : factories(factories), memory(memory) {}

RelationalExpressionParser
RelationalExpressionParser::createDefaultInstance(const Tokenizer &tokenizer, VariablesMemory &memory) {
  vector<shared_ptr<OperationPartFactory> > factories;
  factories.push_back(make_shared<LeftBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_shared<RightBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_shared<ProjectionOperatorFactory>(tokenizer));
  factories.push_back(make_shared<IntersectionOperatorFactory>(tokenizer));
  factories.push_back(make_shared<DataSourceExpressionOperationPartFactory>(tokenizer, memory));
  return RelationalExpressionParser(factories, memory);
}

shared_ptr<AbstractExpression> RelationalExpressionParser::createExpressionFromTokens(
        const std::vector<Token> &tokens) const {
  vector<OperationPart*> infix = createInfixFromTokens(tokens);
  vector<OperationPart*> postfix = createPostfixFromInfix(infix);
  return createExpressionFromPostfix(postfix);
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
  string probableNewAlias = lastAlias.substr(0, lastAlias.size() - 1) + (char) (lastAlias.back() + 1);
  if (!memory.exists(probableNewAlias)) {
    return probableNewAlias;
  }
  return getNextAlias(probableNewAlias);
}

shared_ptr<AbstractExpression> RelationalExpressionParser::createExpressionFromPostfix(
        const std::vector<OperationPart*> &parts) const {
  stack<shared_ptr<AbstractExpression> > expressions;
  string lastAlias;
  string currentAlias;
  for (auto part: parts) {
    if(part->type != OperationPartType::OPERAND && part->type != OperationPartType::LEFT_BRACKET && part->type != OperationPartType::RIGHT_BRACKET) {
      currentAlias = getNextAlias(lastAlias);
      lastAlias = currentAlias;
    }
    part->evaluate(expressions, currentAlias);
    delete part;
  }
  expressions.top()->reset();
  return expressions.top();
}
