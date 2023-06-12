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
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override;
};

class LeftBracketRelationOperand : public OperationPart {
public:
  LeftBracketRelationOperand();
};

class RightBracketRelationOperandFactory : public OperationPartFactory {

public:
  RightBracketRelationOperandFactory(const Tokenizer &tokenizer);
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override;
};

class RightBracketRelationOperand : public OperationPart {
public:
  RightBracketRelationOperand();
};

class ProjectionOperatorFactory : public OperationPartFactory {
public:
  ProjectionOperatorFactory(const Tokenizer &tokenizer);
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override;
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
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override;
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

class IntersectionOperator : public OperationPart {
public:
  IntersectionOperator() : OperationPart(OperationPartType::BINARY_OPERATOR, 9) {}

  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias) override {
    auto right = parts.top();
    parts.pop();
    auto left = parts.top();
    parts.pop();
    return parts.push(std::make_shared<IntersectionExpression>(left, right, operationAlias));
  }
};

class IntersectionOperatorFactory : public OperationPartFactory {
public:
  IntersectionOperatorFactory(const Tokenizer &tokenizer) : OperationPartFactory(tokenizer) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "∩";
  }

  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return new IntersectionOperator();
  }
};

class UnionOperator : public OperationPart {
public:
  UnionOperator() : OperationPart(OperationPartType::BINARY_OPERATOR, 10) {}

  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias) override {
    auto right = parts.top();
    parts.pop();
    auto left = parts.top();
    parts.pop();
    return parts.push(std::make_shared<UnionExpression>(left, right, operationAlias));
  }
};

class UnionOperatorFactory : public OperationPartFactory {
public:
  UnionOperatorFactory(const Tokenizer &tokenizer) : OperationPartFactory(tokenizer) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) {
    return tokens[nextTokenIndex].value == "∪";
  }

  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return new UnionOperator();
  }
};

class ExceptOperator : public OperationPart {
public:
  ExceptOperator() : OperationPart(OperationPartType::BINARY_OPERATOR, 10) {}

  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias) override {
    auto right = parts.top();
    parts.pop();
    auto left = parts.top();
    parts.pop();
    return parts.push(std::make_shared<ExceptExpression>(left, right, operationAlias));
  }
};

class ExceptOperatorFactory : public OperationPartFactory {
public:
  ExceptOperatorFactory(const Tokenizer &tokenizer) : OperationPartFactory(tokenizer) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "\\";
  }

  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return new ExceptOperator();
  }
};

class CartesianProductOperator : public OperationPart {
public:
  CartesianProductOperator() : OperationPart(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::stack<std::shared_ptr<AbstractExpression>> &parts, std::string &operationAlias) override {
    auto right = parts.top();
    parts.pop();
    auto left = parts.top();
    parts.pop();
    return parts.push(std::make_shared<CartesianProductExpression>(left, right, operationAlias));
  }
};

class CartesianProductOperatorFactory : public OperationPartFactory {
public:
  CartesianProductOperatorFactory(const Tokenizer &tokenizer) : OperationPartFactory(tokenizer) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "×";
  }

  OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return new CartesianProductOperator();
  }
};


#endif //SEMESTRAL_EXPRESSION_OPERATION_PART_H
