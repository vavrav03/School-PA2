#include "relational-expression-parser.h"

using namespace std;

RelationalExpressionParser::RelationalExpressionParser(vector<unique_ptr<OperationPartFactory<AbstractDataSource> > > &factories,
                                                       VariablesMemory &memory)
    : factories(std::move(factories)), memory(memory) {}

RelationalExpressionParser
RelationalExpressionParser::createDefaultInstance(VariablesMemory &memory) {
  vector<unique_ptr<OperationPartFactory<AbstractDataSource> > > factories;
  factories.push_back(make_unique<LeftBracketRelationOperandFactory>());
  factories.push_back(make_unique<RightBracketRelationOperandFactory>());
  factories.push_back(make_unique<ProjectionOperatorFactory>());
  factories.push_back(make_unique<IntersectionOperatorFactory>());
  factories.push_back(make_unique<UnionOperatorFactory>());
  factories.push_back(make_unique<ExceptOperatorFactory>());
  factories.push_back(make_unique<CartesianProductOperatorFactory>());
  factories.push_back(make_unique<DataSourceExpressionOperationPartFactory>(memory));
  return RelationalExpressionParser(factories, memory);
}

unique_ptr<AbstractDataSource> RelationalExpressionParser::createExpressionFromTokens(
    const std::vector<Token> &tokens) const {
  return createExpressionFromPostfix(createPostfixFromInfix(createInfixFromTokens(tokens)));
}

vector<unique_ptr<OperationPart<AbstractDataSource> > > RelationalExpressionParser::createInfixFromTokens(const vector<Token> &tokens) const {
  size_t nextTokenIndex = 0;
  vector<unique_ptr<OperationPart<AbstractDataSource> > > infix;
  while (nextTokenIndex < tokens.size()) {
    bool found = false;
    for (auto &factory : factories) {
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

unique_ptr<AbstractDataSource> RelationalExpressionParser::createExpressionFromPostfix(
    const std::vector<unique_ptr<OperationPart<AbstractDataSource> > > &parts) const {
  stack<unique_ptr<AbstractDataSource> > expressions;
  string lastAlias;
  string currentAlias;
  for (auto &part : parts) {
    if (part->type != OperationPartType::OPERAND && part->type != OperationPartType::LEFT_BRACKET
        && part->type != OperationPartType::RIGHT_BRACKET) {
      currentAlias = memory.generateNewAvailableAlias(lastAlias);
      lastAlias = currentAlias;
    }
    part->evaluate(expressions, currentAlias);
  }
  expressions.top()->reset();
  return std::move(expressions.top());
}
