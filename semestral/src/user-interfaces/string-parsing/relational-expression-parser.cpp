#include "./expression-parser.h"

#include "./operator-factories/relational-operation-factories.h"
using namespace std;

template<>
ExpressionParser<AbstractDataSource> ExpressionParser<AbstractDataSource>::getInstance(VariablesMemory &memory) {
  vector<unique_ptr<OperationPartFactory<AbstractDataSource> >> factories;
  // the ones with more characters must be first to avoid matching the shorter ones
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, LeftNaturalAntiJoinOperator>>(
      vector<string>{"!", "<", "*"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, RightNaturalAntiJoinOperator>>(
      vector<string>{"!", "*", ">"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, LeftNaturalSemiJoinOperator>>(
      vector<string>{"<", "*"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, RightNaturalSemiJoinOperator>>(
      vector<string>{"*", ">"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource,
                                                           LeftBracketOperand<AbstractDataSource>>>(
      vector<string>{"{"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource,
                                                           RightBracketOperand<AbstractDataSource>>>(
      vector<string>{"}"}));
  factories.push_back(make_unique<ProjectionOperatorFactory>());
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, IntersectionOperator>>(
      vector<string>{"∩"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, UnionOperator>>(
      vector<string>{"∪"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, ExceptOperator>>(
      vector<string>{"\\"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, CartesianProductOperator>>(
      vector<string>{"×"}));
  factories.push_back(make_unique<CharacterOperatorFactory<AbstractDataSource, NaturalJoinOperator>>(
      vector<string>{"*"}));
  factories.push_back(make_unique<CSVOperandFactory>());
  factories.push_back(make_unique<JSONOperandFactory>());
  factories.push_back(make_unique<VariableOperandFactory>(memory));
  return ExpressionParser(std::move(factories));
}