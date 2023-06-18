#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_

#include "./operation-factory.h"
#include "../tokenizer/token.h"
#include "../../../expression-evaluation/operation-part.h"
#include "../../../expression-evaluation/relational-operation-part.h"
#include "../expression-parser.h"

class ProjectionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  ProjectionOperatorFactory();
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                             size_t &nextTokenIndex) const override;
};

class SelectionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  SelectionOperatorFactory();
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                             size_t &nextTokenIndex) const override;
};

template<typename OperandTarget>
class ThetaJoinOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  ThetaJoinOperatorFactory(const std::vector<std::string> &prefixes, const std::vector<std::string> &postfixes)
      : prefixes(prefixes), postfixes(postfixes) {}
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    size_t examinedIndex = nextTokenIndex;
    if (examinedIndex + prefixes.size() + postfixes.size() > tokens.size()) {
      return false;
    }
    for (size_t i = 0; i < prefixes.size(); i++) {
      if (tokens[examinedIndex + i].value != prefixes[i]) {
        return false;
      }
    }
    examinedIndex += prefixes.size();
    if (tokens[examinedIndex].value != "[") {
      return false;
    }
    examinedIndex++;
    // search for matching ] - no nesting
    bool found = false;
    std::vector<Token> subTokens;
    for (; examinedIndex < tokens.size(); examinedIndex++) {
      if (tokens[examinedIndex].value == "]") {
        found = true;
        break;
      }
      subTokens.push_back(tokens[examinedIndex]);
    }
    if (!found) {
      return false;
    }
    try {
      ExpressionParser<AbstractBooleanExpression>::getInstance().createExpressionFromTokens(subTokens);
    } catch (std::exception &e) {
      return false; // invalid expression
    }
    for (size_t i = 0; i < postfixes.size(); i++) {
      if (tokens[examinedIndex + i].value != postfixes[i]) {
        return false;
      }
    }
    return true;
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                             size_t &nextTokenIndex) const override {
    nextTokenIndex += prefixes.size() + 1;
    std::vector<Token> subTokens;
    for (; nextTokenIndex < tokens.size(); nextTokenIndex++) {
      if (tokens[nextTokenIndex].value == "]") {
        break;
      }
      subTokens.push_back(tokens[nextTokenIndex]);
    }
    nextTokenIndex += 1;
    nextTokenIndex += postfixes.size();
    auto condition =
        ExpressionParser<AbstractBooleanExpression>::getInstance().createExpressionFromTokens(subTokens);
    return std::make_unique<OperandTarget>(std::move(condition));
  }
 private:
  std::vector<std::string> prefixes;
  std::vector<std::string> postfixes;
};

class VariableOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  explicit VariableOperandFactory(VariablesMemory &memory);
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                             size_t &nextTokenIndex) const override;
 private:
  VariablesMemory &memory;
};

class CSVOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  explicit CSVOperandFactory();
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                             size_t &nextTokenIndex) const override;
};

class JSONOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  explicit JSONOperandFactory();
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                             size_t &nextTokenIndex) const override;
};

#endif //SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_
