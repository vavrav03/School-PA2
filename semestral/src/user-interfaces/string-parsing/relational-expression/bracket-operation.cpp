#include "./relational-expression-parser.h"

using namespace std;

LeftBracketRelationOperandFactory::LeftBracketRelationOperandFactory(const Tokenizer &tokenizer) : OperationPartFactory(
        tokenizer) {}

bool LeftBracketRelationOperandFactory::canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const {
  return tokens[nextTokenIndex].value == "{";
}

OperationPart *LeftBracketRelationOperandFactory::create(const std::vector<Token> &tokens, int &nextTokenIndex) const {
  nextTokenIndex++;
  return new LeftBracketRelationOperand();
}

LeftBracketRelationOperand::LeftBracketRelationOperand() : OperationPart(OperationPartType::LEFT_BRACKET, 999) {}

RightBracketRelationOperandFactory::RightBracketRelationOperandFactory(const Tokenizer &tokenizer)
        : OperationPartFactory(tokenizer) {}

bool RightBracketRelationOperandFactory::canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const {
  return tokens[nextTokenIndex].value == "}";
}

OperationPart *RightBracketRelationOperandFactory::create(const std::vector<Token> &tokens, int &nextTokenIndex) const {
  nextTokenIndex++;
  return new RightBracketRelationOperand();
}

RightBracketRelationOperand::RightBracketRelationOperand() : OperationPart(OperationPartType::RIGHT_BRACKET, 999) {}