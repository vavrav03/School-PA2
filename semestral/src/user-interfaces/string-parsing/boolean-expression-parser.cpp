#include "./expression-parser.h"

#include "./operator-factories/boolean-operation-factories.h"
#include "../../expression-evaluation/boolean-operation-part.h"
using namespace std;

template<>
ExpressionParser<AbstractBooleanExpression> ExpressionParser<AbstractBooleanExpression>::getInstance() {
  vector<unique_ptr<OperationPartFactory<AbstractBooleanExpression>>> factories;
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression,
                                                           LeftBracketOperand<AbstractBooleanExpression>>>
                          (vector<string>{"("}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression,
                                                           RightBracketOperand<AbstractBooleanExpression>>>
                          (vector<string>{")"}));
  factories.push_back(make_unique<BooleanOperandFactory<NoEqualOperand>>
                          (vector<string>{"!", "="}));
  factories.push_back(make_unique<BooleanOperandFactory<LessThanOrEqualOperand>>
                          (vector<string>{"<", "="}));
  factories.push_back(make_unique<BooleanOperandFactory<GreaterThanOrEqualOperand>>
                          (vector<string>{">", "="}));
  factories.push_back(make_unique<BooleanOperandFactory<EqualOperand>>
                          (vector<string>{"="}));
  factories.push_back(make_unique<BooleanOperandFactory<LessThanOperand>>
                          (vector<string>{"<"}));
  factories.push_back(make_unique<BooleanOperandFactory<GreaterThanOperand>>
                          (vector<string>{">"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, NotOperator>>
                          (vector<string>{"'"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, AndOperator>>
                          (vector<string>{"∧"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, OrOperator>>
                          (vector<string>{"∨"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, XorOperator>>
                          (vector<string>{"⊕"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, ImpliesOperator>>
                          (vector<string>{"⇒"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, EquivalenceOperator>>
                          (vector<string>{"⇔"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, NandOperator>>
                          (vector<string>{"↓"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractBooleanExpression, NorOperator>>
                          (vector<string>{"↑"}));
  return ExpressionParser<AbstractBooleanExpression>(std::move(factories));
}