#ifndef SEMESTRAL_EXPRESSION_OPERATION_PART_H
#define SEMESTRAL_EXPRESSION_OPERATION_PART_H

#include "operation-part.h"
#include <string>
#include <stack>
#include "../data-sources/expressions/expressions.h"
#include "../user-interfaces/string-parsing/tokenizer/token.h"
#include "../user-interfaces/string-parsing/tokenizer/tokenizer.h"
#include "../user-interfaces/variables-memory/variables-memory.h"
#include "../data-sources/file/csv.h"
#include "../data-sources/file/json.h"

class LeftBracketRelationOperand : public OperationPart<AbstractDataSource> {
 public:
  LeftBracketRelationOperand() : OperationPart<AbstractDataSource>(OperationPartType::LEFT_BRACKET, 999) {}
};

class RightBracketRelationOperand : public OperationPart<AbstractDataSource> {
 public:
  RightBracketRelationOperand() : OperationPart<AbstractDataSource>(OperationPartType::RIGHT_BRACKET, 999) {}
};

class VariableOperand : public OperationPart<AbstractDataSource> {
 public:
  VariableOperand(std::unique_ptr<AbstractDataSource> expression) : OperationPart<AbstractDataSource>(
      OperationPartType::OPERAND, 1999), expression(std::move(expression)) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    parts.push_back(std::move(expression));
  }

 private:
  std::unique_ptr<AbstractDataSource> expression;
};

class CSVOperand : public OperationPart<AbstractDataSource> {
 public:
  CSVOperand(const std::string &path)
      : OperationPart<AbstractDataSource>(OperationPartType::OPERAND, 1999),
        path(path) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    parts.push_back(std::make_unique<CSVDataSource>(path));
  }

 private:
  std::string path;
};

class JSONOperand : public OperationPart<AbstractDataSource> {
 public:
  JSONOperand(const std::string &path)
      : OperationPart<AbstractDataSource>(OperationPartType::OPERAND, 1999),
        path(path) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    parts.push_back(std::make_unique<JSONDataSource>(path));
  }

 private:
  std::string path;
};

class ProjectionOperator : public OperationPart<AbstractDataSource> {
 public:
  ProjectionOperator(const std::vector<std::string> &header,
                     const std::unordered_map<std::string, std::string> &aliasToOld) : OperationPart(
      OperationPartType::POSTFIX_UNARY_OPERATOR, 50), header(header), aliasToOldName(aliasToOld) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto projection =
        std::make_unique<ProjectionExpression>(std::move(parts.back()), header, aliasToOldName);
    parts.pop_back();
    parts.push_back(std::move(projection));
  }
 private:
  std::vector<std::string> header;
  std::unordered_map<std::string, std::string> aliasToOldName;
};

class IntersectionOperator : public OperationPart<AbstractDataSource> {
 public:
  IntersectionOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 9) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto right = std::move(parts.back());
    parts.pop_back();
    auto left = std::move(parts.back());
    parts.pop_back();
    parts.push_back(std::make_unique<IntersectionExpression>(std::move(left), std::move(right)));
  }
};

class UnionOperator : public OperationPart<AbstractDataSource> {
 public:
  UnionOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 10) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto right = std::move(parts.back());
    parts.pop_back();
    auto left = std::move(parts.back());
    parts.pop_back();
    parts.push_back(std::make_unique<UnionExpression>(std::move(left), std::move(right)));
  }
};

class ExceptOperator : public OperationPart<AbstractDataSource> {
 public:
  ExceptOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 10) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto right = std::move(parts.back());
    parts.pop_back();
    auto left = std::move(parts.back());
    parts.pop_back();
    parts.push_back(std::make_unique<ExceptExpression>(std::move(left), std::move(right)));
  }
};

class CartesianProductOperator : public OperationPart<AbstractDataSource> {
 public:
  CartesianProductOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto right = std::move(parts.back());
    parts.pop_back();
    auto left = std::move(parts.back());
    parts.pop_back();
    parts.push_back(std::make_unique<CartesianProductExpression>(std::move(left), std::move(right)));
  }
};

class NaturalJoinOperator : public OperationPart<AbstractDataSource> {
 public:
  NaturalJoinOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto right = std::move(parts.back());
    parts.pop_back();
    auto left = std::move(parts.back());
    parts.pop_back();
    parts.push_back(std::make_unique<NaturalJoinExpression>(std::move(left), std::move(right)));
  }
};

class LeftNaturalSemiJoinOperator : public OperationPart<AbstractDataSource> {
 public:
  LeftNaturalSemiJoinOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto leftHeader = parts[parts.size() - 2]->getHeaderVector();
    NaturalJoinOperator().evaluate(parts);
    ProjectionOperator(leftHeader, std::unordered_map<std::string, std::string>()).evaluate(parts);
  }
};

class RightNaturalSemiJoinOperator : public OperationPart<AbstractDataSource> {
 public:
  RightNaturalSemiJoinOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    const std::vector<std::string> rightHeader = parts.back()->getHeaderVector();
    NaturalJoinOperator().evaluate(parts);
    ProjectionOperator(rightHeader, std::unordered_map<std::string, std::string>()).evaluate(parts);
  }
};

class LeftNaturalAntiJoin : public OperationPart<AbstractDataSource> {
 public:
  LeftNaturalAntiJoin() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto leftExpressionClone = parts[parts.size() - 2]->clone();
    LeftNaturalSemiJoinOperator().evaluate(parts);
    parts.push_back(std::make_unique<ExceptExpression>(std::move(leftExpressionClone), std::move(parts.back())));
  }
};

class RightNaturalAntiJoin: public OperationPart<AbstractDataSource> {
 public:
  RightNaturalAntiJoin() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::vector<std::unique_ptr<AbstractDataSource>> &parts) override {
    auto rightExpressionClone = parts.back()->clone();
    RightNaturalSemiJoinOperator().evaluate(parts);
    parts.push_back(std::make_unique<ExceptExpression>(std::move(rightExpressionClone), std::move(parts.back())));
  }
};

#endif //SEMESTRAL_EXPRESSION_OPERATION_PART_H
