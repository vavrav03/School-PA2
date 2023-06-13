#ifndef SEMESTRAL_OPERATION_PART_H
#define SEMESTRAL_OPERATION_PART_H

#include "tokenizer/tokenizer.h"
#include "../../data-sources/expressions/expressions.h"
#include <stack>
#include <iostream>

enum class OperationPartType {
  OPERAND,
  PREFIX_UNARY_OPERATOR,
  POSTFIX_UNARY_OPERATOR,
  BINARY_OPERATOR,
  LEFT_BRACKET,
  RIGHT_BRACKET
};

class OperationPart {

public:
  OperationPart(OperationPartType type, int priority) : type(type),
                                                        priority(priority) {}

  const OperationPartType type;
  const int priority;
  virtual ~OperationPart() = default;

  virtual void evaluate(std::stack<std::shared_ptr<AbstractDataSource>> &evaluatedParts, std::string &operationAlias) {
    // do nothing
  };
};

class OperationPartFactory {

public:
  OperationPartFactory(const Tokenizer &tokenizer) : tokenizer(tokenizer) {}

  /**
   * This method create OperationPart. It assumes that canCreate() returned true - no validity checks are performed
   * It also sets new value of nextTokenIndex
   * @param tokens
   * @param nextTokenIndex It is guaranteed to never exceed tokens.size(). Item with this index potentially belongs to this operation part
   * @return
   */
  virtual bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const = 0;
  virtual OperationPart *create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const = 0;
  virtual ~OperationPartFactory() = default;
protected:
  const Tokenizer &tokenizer;
};

/**
 * Create postfix ordering of OperationPart from infix using shunning-yard algorithm.
 * @param infix
 * @return
 */
std::vector<OperationPart*> createPostfixFromInfix(const std::vector<OperationPart*> &infix);


#endif //SEMESTRAL_OPERATION_PART_H
