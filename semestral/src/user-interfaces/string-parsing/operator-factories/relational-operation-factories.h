#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_RELATIONAL_OPERATOR_FACTORIES_H_

#include "./operation-factory.h"
#include "../tokenizer/token.h"
#include "../../../expression-evaluation/operation-part.h"
#include "../../../expression-evaluation/relational-operation-part.h"

class ProjectionOperatorFactory : public OperationPartFactory<AbstractDataSource> {
 public:
  ProjectionOperatorFactory();
  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override;
  std::unique_ptr<OperationPart<AbstractDataSource> > create(const std::vector<Token> &tokens,
                                                             size_t &nextTokenIndex) const override;
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
