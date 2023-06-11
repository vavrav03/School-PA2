#ifndef SEMESTRAL_EXPRESSION_OPERATION_PART_H
#define SEMESTRAL_EXPRESSION_OPERATION_PART_H

#include "../operation-part.h"
#include <string>
#include "../../../data-sources/expressions/expressions.h"
#include "../tokenizer/token.h"
#include "../tokenizer/tokenizer.h"
#include "../../abstract/variables-memory.h"

class LeftBracketRelationOperandFactory : public OperationPartFactory {
public:
  LeftBracketRelationOperandFactory(const Tokenizer &tokenizer);
  bool canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, int &nextTokenIndex) const override;
};

class LeftBracketRelationOperand : public OperationPart {
public:
  LeftBracketRelationOperand();
};

class RightBracketRelationOperandFactory : public OperationPartFactory {

public:
  RightBracketRelationOperandFactory(const Tokenizer &tokenizer);
  bool canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, int &nextTokenIndex) const override;
};

class RightBracketRelationOperand : public OperationPart {
public:
  RightBracketRelationOperand();
};

class ProjectionOperatorFactory : public OperationPartFactory {
public:
  ProjectionOperatorFactory(const Tokenizer &tokenizer);
  bool canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, int &nextTokenIndex) const override;
};

class ProjectionOperator : public OperationPart {
public:
  ProjectionOperator(const std::vector<std::string> &header,
                     const std::unordered_map<std::string, std::string> &aliasToOldName);

  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias);
private:
  std::vector<std::string> header;
  std::unordered_map<std::string, std::string> aliasToOldName;
};

class DataSourceExpressionOperationPartFactory : public OperationPartFactory {
public:
  DataSourceExpressionOperationPartFactory(const Tokenizer &tokenizer, VariablesMemory &memory);
  bool canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, int &nextTokenIndex) const override;
private:
  VariablesMemory &memory;
};

class DataSourceExpressionOperationPart : public OperationPart {
public:
  DataSourceExpressionOperationPart(const std::shared_ptr<AbstractExpression> &expression);
  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias) override;
private:
  std::shared_ptr<AbstractExpression> expression;
};

class IntersectionOperatorFactory : public OperationPartFactory {
public:
  IntersectionOperatorFactory(const Tokenizer &tokenizer);
  bool canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, int &nextTokenIndex) const override;
};

class IntersectionOperator : public OperationPart {
public:
  IntersectionOperator();
  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias) override;
};

class UnionOperatorFactory : public OperationPartFactory {
public:
  UnionOperatorFactory(const Tokenizer &tokenizer);
  bool canCreate(const std::vector<Token> &tokens, int nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, int &nextTokenIndex) const override;
};

class UnionOperator : public OperationPart {
public:
  UnionOperator();
  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias) override;
};


#endif //SEMESTRAL_EXPRESSION_OPERATION_PART_H
