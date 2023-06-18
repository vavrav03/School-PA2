#include "./relational-operation-factories.h"
#include "../expression-parser.h"

SelectionOperatorFactory::SelectionOperatorFactory() {}

bool SelectionOperatorFactory::canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const {
  if (tokens[nextTokenIndex].value != "(") {
    return false;
  }
  int bracketCount = 1;
  for (int i = nextTokenIndex + 1; i < tokens.size(); i++) {
    if (tokens[i].value == "(") {
      bracketCount++;
    } else if (tokens[i].value == ")") {
      bracketCount--;
    }
    if (bracketCount == 0) {
      return true;
    }
  }
  return false;
}

std::unique_ptr<OperationPart<AbstractDataSource> > SelectionOperatorFactory::create(const std::vector<Token> &tokens,
                                                                                     size_t &nextTokenIndex) const {
  nextTokenIndex++;
  std::vector<Token> subTokens;
  int bracketCount = 1;
  for (int i = nextTokenIndex; i < tokens.size(); i++) {
    if (tokens[i].value == "(") {
      bracketCount++;
    } else if (tokens[i].value == ")") {
      bracketCount--;
    }
    if (bracketCount == 0) {
      nextTokenIndex = i + 1;
      break;
    }
    subTokens.push_back(tokens[i]);
  }
  auto expression =
      ExpressionParser<AbstractBooleanExpression>::getInstance().createExpressionFromTokens(subTokens);
  return std::make_unique<SelectionOperator>(std::move(expression));
}