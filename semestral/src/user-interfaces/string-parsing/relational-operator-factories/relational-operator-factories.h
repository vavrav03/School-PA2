#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_

#include "../tokenizer/token.h"
#include "../../../expression-evaluation/operation-part.h"
#include "../../../expression-evaluation/expression-operation-part.h"

class LeftBracketRelationOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  LeftBracketRelationOperandFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "{";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<LeftBracketRelationOperand>();
  }
};

class RightBracketRelationOperandFactory : public OperationPartFactory<AbstractDataSource> {

 public:
  RightBracketRelationOperandFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "}";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<RightBracketRelationOperand>();
  }
};

class ProjectionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  ProjectionOperatorFactory();
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override;
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

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    if (!memory.exists(tokens[nextTokenIndex].value)) {
      throw std::runtime_error("Variable " + tokens[nextTokenIndex].value + " does not exist.");
    }
    std::unique_ptr<OperationPart<AbstractDataSource> >
        returnValue = std::make_unique<VariableOperand>(memory.get(tokens[nextTokenIndex].value));
    nextTokenIndex++;
    return returnValue;
  }

 private:
  VariablesMemory &memory;
};

class IntersectionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  IntersectionOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "∩";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<IntersectionOperator>();
  }
};

class UnionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  UnionOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "∪";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<UnionOperator>();
  }
};

class ExceptOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  ExceptOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "\\";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<ExceptOperator>();
  }
};

class CartesianProductOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  CartesianProductOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "×";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<CartesianProductOperator>();
  }
};

class NaturalJoinOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  NaturalJoinOperatorFactory() : OperationPartFactory<AbstractDataSource>() {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].value == "*";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    nextTokenIndex++;
    return std::make_unique<NaturalJoinOperator>();
  }
};

class CSVOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  CSVOperandFactory(VariablesMemory &memory) : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].quoted && getExtensionFromPath(tokens[nextTokenIndex].value) == "csv";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    std::string path = tokens[nextTokenIndex].value;
    auto returnValue = std::make_unique<CSVOperand>(path);
    nextTokenIndex++;
    return returnValue;
  }
  VariablesMemory &memory;
};

class JSONOperandFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  JSONOperandFactory(VariablesMemory &memory) : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    return tokens[nextTokenIndex].quoted && getExtensionFromPath(tokens[nextTokenIndex].value) == "json";
  }

  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                            size_t &nextTokenIndex) const override {
    std::string path = tokens[nextTokenIndex].value;
    auto returnValue = std::make_unique<JSONOperand>(path);
    nextTokenIndex++;
    return returnValue;
  }
  VariablesMemory &memory;
};

#endif //SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_
