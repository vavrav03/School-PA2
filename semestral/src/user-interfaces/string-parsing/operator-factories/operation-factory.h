#ifndef SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_OPERATOR_FACTORIES_OPERATION_FACTORY_H_
#define SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_OPERATOR_FACTORIES_OPERATION_FACTORY_H_

#include "../../../expression-evaluation/operation-part.h"

template<typename T>
class OperationPartFactory {

 public:
  OperationPartFactory() {}

  /**
   * This method create OperationPart. It assumes that canCreate() returned true - no validity checks are performed
   * It also sets new value of nextTokenIndex
   * @param tokens
   * @param nextTokenIndex It is guaranteed to never exceed tokens.size(). Item with this index potentially belongs to this operation part
   * @return
   */
  virtual bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const = 0;
  virtual std::unique_ptr<OperationPart<T> > create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const = 0;
  virtual ~OperationPartFactory() = default;
};

template<typename Generic, typename Concrete>
class CharacterOperatorFactory : public OperationPartFactory<Generic> {

 public:
  CharacterOperatorFactory(const std::vector<std::string> &operators) : operatorParts({operators}) {}

  bool canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const override {
    if (nextTokenIndex + operatorParts.size() > tokens.size()) {
      return false;
    }
    for (size_t i = 0; i < operatorParts.size(); i++) {
      if (tokens[nextTokenIndex + i].value != operatorParts[i]) {
        return false;
      }
    }
    return true;
  }
  std::unique_ptr<OperationPart<Generic> > create(const std::vector<Token> &tokens,
                                                  size_t &nextTokenIndex) const override {
    nextTokenIndex += operatorParts.size();
    return std::make_unique<Concrete>();
  }
 private:
  std::vector<std::string> operatorParts;
};

#endif //SEMESTRAL_SRC_USER_INTERFACES_STRING_PARSING_OPERATOR_FACTORIES_OPERATION_FACTORY_H_
