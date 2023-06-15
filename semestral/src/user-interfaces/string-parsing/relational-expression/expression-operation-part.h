#ifndef SEMESTRAL_EXPRESSION_OPERATION_PART_H
#define SEMESTRAL_EXPRESSION_OPERATION_PART_H

#include "../operation-part.h"
#include <string>
#include <stack>
#include "../../../data-sources/expressions/expressions.h"
#include "../tokenizer/token.h"
#include "../tokenizer/tokenizer.h"
#include "../../abstract/variables-memory.h"
#include "../../../data-sources/file/csv.h"
#include "../../../data-sources/file/json.h"

class LeftBracketRelationOperand : public OperationPart<AbstractDataSource> {
 public:
  LeftBracketRelationOperand() : OperationPart<AbstractDataSource>(OperationPartType::LEFT_BRACKET, 999) {}
};

class LeftBracketRelationOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  LeftBracketRelationOperandFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "{";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<LeftBracketRelationOperand>();
  }
};

class RightBracketRelationOperand : public OperationPart<AbstractDataSource> {
 public:
  RightBracketRelationOperand() : OperationPart<AbstractDataSource>(OperationPartType::RIGHT_BRACKET, 999) {}
};

class RightBracketRelationOperandFactory : public OperationPartFactory<AbstractDataSource> {

 public:
  RightBracketRelationOperandFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "}";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<RightBracketRelationOperand>();
  }
};

class ProjectionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  ProjectionOperatorFactory();
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override;
};

class ProjectionOperator : public OperationPart<AbstractDataSource> {
 public:
  ProjectionOperator(const std::vector<std::string> &header,
                     const std::unordered_map<std::string, std::string> &aliasToOldName);

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias);
 private:
  std::vector<std::string> header;
  std::unordered_map<std::string, std::string> aliasToOldName;
};

class VariableOperand : public OperationPart<AbstractDataSource> {
 public:
  VariableOperand(std::unique_ptr<AbstractDataSource> expression) : OperationPart<AbstractDataSource>(
      OperationPartType::OPERAND, 1999), expression(std::move(expression)) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    parts.push(std::move(expression));
  }

 private:
  std::unique_ptr<AbstractDataSource> expression;
};

class VariableOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  VariableOperandFactory(VariablesMemory &memory) : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    if (tokens[nextTokenIndex].quoted) {
      return true;
    }
    return !Tokenizer::getInstnace().isSpecialCharacter(tokens[nextTokenIndex].value);
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    if (!memory.exists(tokens[nextTokenIndex].value)) {
      throw std::runtime_error("Variable " + tokens[nextTokenIndex].value + " does not exist.");
    }
    std::unique_ptr<OperationPart<AbstractDataSource>>
        returnValue = std::make_unique<VariableOperand>(memory.get(tokens[nextTokenIndex].value));
    nextTokenIndex++;
    return returnValue;
  }

 private:
  VariablesMemory &memory;
};

class IntersectionOperator : public OperationPart<AbstractDataSource> {
 public:
  IntersectionOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 9) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    auto right = std::move(parts.top());
    parts.pop();
    auto left = std::move(parts.top());
    parts.pop();
    parts.push(std::make_unique<IntersectionExpression>(std::move(left), std::move(right), operationAlias));
  }
};

class IntersectionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  IntersectionOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "∩";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<IntersectionOperator>();
  }
};

class UnionOperator : public OperationPart<AbstractDataSource> {
 public:
  UnionOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 10) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    auto right = std::move(parts.top());
    parts.pop();
    auto left = std::move(parts.top());
    parts.pop();
    parts.push(std::make_unique<UnionExpression>(std::move(left), std::move(right), operationAlias));
  }
};

class UnionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  UnionOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "∪";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<UnionOperator>();
  }
};

class ExceptOperator : public OperationPart<AbstractDataSource> {
 public:
  ExceptOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 10) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    auto right = std::move(parts.top());
    parts.pop();
    auto left = std::move(parts.top());
    parts.pop();
    parts.push(std::make_unique<ExceptExpression>(std::move(left), std::move(right), operationAlias));
  }
};

class ExceptOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  ExceptOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "\\";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<ExceptOperator>();
  }
};

class CartesianProductOperator : public OperationPart<AbstractDataSource> {
 public:
  CartesianProductOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    auto right = std::move(parts.top());
    parts.pop();
    auto left = std::move(parts.top());
    parts.pop();
    parts.push(std::make_unique<CartesianProductExpression>(std::move(left), std::move(right), operationAlias));
  }
};

class CartesianProductOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  CartesianProductOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "×";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<CartesianProductOperator>();
  }
};

class NaturalJoinOperator : public OperationPart<AbstractDataSource> {
 public:
  NaturalJoinOperator() : OperationPart<AbstractDataSource>(OperationPartType::BINARY_OPERATOR, 11) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    auto right = std::move(parts.top());
    parts.pop();
    auto left = std::move(parts.top());
    parts.pop();
    parts.push(std::make_unique<NaturalJoinExpression>(std::move(left), std::move(right), operationAlias));
  }
};

class NaturalJoinOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  NaturalJoinOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "*";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<NaturalJoinOperator>();
  }
};

class CSVOperand : public OperationPart<AbstractDataSource> {
 public:
  CSVOperand(const std::string &path, const std::string &name) : OperationPart<AbstractDataSource>(OperationPartType::OPERAND, 1999),
                                        path(path), name(name) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    const auto usedAlias = getNameWithoutExtension(path);

    parts.push(std::make_unique<CSVDataSource>(path, name));
  }

 private:
  std::string path;
  std::string name;
};

class CSVOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  CSVOperandFactory(VariablesMemory &memory) : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].quoted && getExtensionFromPath(tokens[nextTokenIndex].value) == "csv";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    std::string path = tokens[nextTokenIndex].value;
    std::string name = memory.getAvailableAlias(getNameWithoutExtension(path));
    auto returnValue = std::make_unique<CSVOperand>(path, name);
    nextTokenIndex++;
    return returnValue;
  }
  VariablesMemory &memory;
};

class JSONOperand : public OperationPart<AbstractDataSource> {
 public:
  JSONOperand(const std::string &path, const std::string &name)
      : OperationPart<AbstractDataSource>(OperationPartType::OPERAND, 1999),
        path(path), name(name) {}

  void evaluate(std::stack<std::unique_ptr<AbstractDataSource>> &parts, std::string &operationAlias) override {
    parts.push(std::make_unique<JSONDataSource>(path, name));
  }

 private:
  std::string path;
  std::string name;
};

class JSONOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  JSONOperandFactory(VariablesMemory &memory) : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].quoted && getExtensionFromPath(tokens[nextTokenIndex].value) == "json";
  }

  std::unique_ptr<OperationPart<AbstractDataSource>> create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    std::string path = tokens[nextTokenIndex].value;
    std::string name = memory.getAvailableAlias(getNameWithoutExtension(path));
    auto returnValue = std::make_unique<JSONOperand>(path, name);
    nextTokenIndex++;
    return returnValue;
  }
  VariablesMemory &memory;
};

#endif //SEMESTRAL_EXPRESSION_OPERATION_PART_H
