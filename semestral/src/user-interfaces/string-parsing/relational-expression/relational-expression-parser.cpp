#include "relational-expression-parser.h"

using namespace std;

RelationalExpressionParser::RelationalExpressionParser(vector<unique_ptr<OperationPartFactory> > &factories,
                                                       VariablesMemory &memory)
    : factories(std::move(factories)), memory(memory) {}

RelationalExpressionParser
RelationalExpressionParser::createDefaultInstance(const Tokenizer &tokenizer, VariablesMemory &memory) {
  vector<unique_ptr<OperationPartFactory> > factories;
  factories.push_back(make_unique<LeftBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_unique<RightBracketRelationOperandFactory>(tokenizer));
  factories.push_back(make_unique<ProjectionOperatorFactory>(tokenizer));
  factories.push_back(make_unique<IntersectionOperatorFactory>(tokenizer));
  factories.push_back(make_unique<UnionOperatorFactory>(tokenizer));
  factories.push_back(make_unique<ExceptOperatorFactory>(tokenizer));
  factories.push_back(make_unique<CartesianProductOperatorFactory>(tokenizer));
  factories.push_back(make_unique<DataSourceExpressionOperationPartFactory>(tokenizer, memory));
  return RelationalExpressionParser(factories, memory);
}

unique_ptr<AbstractDataSource> RelationalExpressionParser::createExpressionFromTokens(
    const std::vector<Token> &tokens) const {
  return createExpressionFromPostfix(createPostfixFromInfix(createInfixFromTokens(tokens)));
}

vector<unique_ptr<OperationPart> > RelationalExpressionParser::createInfixFromTokens(const vector<Token> &tokens) const {
  size_t nextTokenIndex = 0;
  vector<unique_ptr<OperationPart> > infix;
  while (nextTokenIndex < tokens.size()) {
    bool found = false;
    for (auto& factory : factories) {
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
    const std::vector<unique_ptr<OperationPart> > &parts) const {
  stack<unique_ptr<AbstractDataSource> > expressions;
  string lastAlias;
  string currentAlias;
  for (auto& part : parts) {
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
