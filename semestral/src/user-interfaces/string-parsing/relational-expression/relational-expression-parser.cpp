#include "relational-expression-parser.h"

using namespace std;

RelationalExpressionParser::RelationalExpressionParser(vector<shared_ptr<OperationPartFactory> > &factories,
                                                       VariablesMemory &memory)
    : factories(factories), memory(memory) {}

RelationalExpressionParser
RelationalExpressionParser::createDefaultInstance(const Tokenizer &tokenizer, VariablesMemory &memory) {
  vector<shared_ptr<OperationPartFactory> > factories;
  factories.push_back(make_shared<LeftBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_shared<RightBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_shared<ProjectionOperatorFactory>(tokenizer));
  factories.push_back(make_shared<IntersectionOperatorFactory>(tokenizer));
  factories.push_back(make_shared<UnionOperatorFactory>(tokenizer));
  factories.push_back(make_shared<ExceptOperatorFactory>(tokenizer));
  factories.push_back(make_shared<CartesianProductOperatorFactory>(tokenizer));
  factories.push_back(make_shared<DataSourceExpressionOperationPartFactory>(tokenizer, memory));
  return RelationalExpressionParser(factories, memory);
}

shared_ptr<AbstractDataSource> RelationalExpressionParser::createExpressionFromTokens(
    const std::vector<Token> &tokens) const {
  vector<OperationPart *> infix = createInfixFromTokens(tokens);
  vector<OperationPart *> postfix = createPostfixFromInfix(infix);
  return createExpressionFromPostfix(postfix);
}

vector<OperationPart *> RelationalExpressionParser::createInfixFromTokens(const vector<Token> &tokens) const {
  size_t nextTokenIndex = 0;
  vector<OperationPart *> infix;
  while (nextTokenIndex < tokens.size()) {
    bool found = false;
    for (auto factory : factories) {
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

shared_ptr<AbstractDataSource> RelationalExpressionParser::createExpressionFromPostfix(
    const std::vector<OperationPart *> &parts) const {
  stack<shared_ptr<AbstractDataSource> > expressions;
  string lastAlias;
  string currentAlias;
  for (auto part : parts) {
    if (part->type != OperationPartType::OPERAND && part->type != OperationPartType::LEFT_BRACKET
        && part->type != OperationPartType::RIGHT_BRACKET) {
      currentAlias = memory.generateNewAvailableAlias(lastAlias);
      lastAlias = currentAlias;
    }
    part->evaluate(expressions, currentAlias);
    delete part;
  }
  expressions.top()->reset();
  return expressions.top();
}
