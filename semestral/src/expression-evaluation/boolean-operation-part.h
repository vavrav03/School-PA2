#ifndef SEMESTRAL_SRC_EXPRESSION_EVALUATION_BOOLEAN_OPERATION_PART_H_
#define SEMESTRAL_SRC_EXPRESSION_EVALUATION_BOOLEAN_OPERATION_PART_H_

#include "./operation-part.h"

class BinaryPrimaryBooleanOperand : public OperationPart<bool> {
 public:
  BinaryPrimaryBooleanOperand(const std::string &leftName, const std::string &rightName)
      : OperationPart<bool>(OperationPartType::OPERAND, 999),
        leftName(leftName),
        rightName(rightName) {}

 protected:
  std::string leftName;
  std::string rightName;
};

class EqualityOperand : public BinaryPrimaryBooleanOperand {
 public:
  EqualityOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand(leftName, rightName) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    evaluatedParts.push_back(std::make_unique<bool>(leftName == rightName));
  }
};

class InequalityOperand : public BinaryPrimaryBooleanOperand {
 public:
  InequalityOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand(leftName, rightName) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    evaluatedParts.push_back(std::make_unique<bool>(leftName != rightName));
  }
};

class LessThanOperand : public BinaryPrimaryBooleanOperand {
 public:
  LessThanOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand(leftName, rightName) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    evaluatedParts.push_back(std::make_unique<bool>(leftName < rightName));
  }
};

class LessThanOrEqualOperand : public BinaryPrimaryBooleanOperand {
 public:
  LessThanOrEqualOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand(leftName, rightName) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    evaluatedParts.push_back(std::make_unique<bool>(leftName <= rightName));
  }
};

class GreaterThanOperand : public BinaryPrimaryBooleanOperand {
 public:
  GreaterThanOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand(leftName, rightName) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    evaluatedParts.push_back(std::make_unique<bool>(leftName > rightName));
  }
};

class GreaterThanOrEqualOperand : public BinaryPrimaryBooleanOperand {
 public:
  GreaterThanOrEqualOperand(const std::string &leftName, const std::string &rightName)
      : BinaryPrimaryBooleanOperand(leftName, rightName) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    evaluatedParts.push_back(std::make_unique<bool>(leftName >= rightName));
  }
};

class AndOperator : public OperationPart<bool> {
 public:
  AndOperator() : OperationPart<bool>(OperationPartType::BINARY_OPERATOR, 10) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<bool>(*left && *right));
  };
};

class OrOperator : public OperationPart<bool> {
 public:
  OrOperator() : OperationPart<bool>(OperationPartType::BINARY_OPERATOR, 9) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<bool>(*left || *right));
  };
};

class ImpliesOperator : public OperationPart<bool> {
 public:
  ImpliesOperator() : OperationPart<bool>(OperationPartType::BINARY_OPERATOR, 9) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<bool>(!*left || *right));
  };
};

class EquivalenceOperator : public OperationPart<bool> {
 public:
  EquivalenceOperator() : OperationPart<bool>(OperationPartType::BINARY_OPERATOR, 9) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<bool>(!(*left ^ *right)));
  };
};

class XorOperator : public OperationPart<bool> {
 public:
  XorOperator() : OperationPart<bool>(OperationPartType::BINARY_OPERATOR, 9) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<bool>(*left ^ *right));
  };
};

class NorOperator : public OperationPart<bool> {
 public:
  NorOperator() : OperationPart<bool>(OperationPartType::BINARY_OPERATOR, 9) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<bool>(!(*left || *right)));
  };
};

class NandOperator : public OperationPart<bool> {
 public:
  NandOperator() : OperationPart<bool>(OperationPartType::BINARY_OPERATOR, 9) {}
  virtual void evaluate(std::vector<std::unique_ptr<bool> > &evaluatedParts) override {
    auto right = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    auto left = std::move(evaluatedParts.back());
    evaluatedParts.pop_back();
    evaluatedParts.push_back(std::make_unique<bool>(!(*left && *right)));
  };
};

#endif //SEMESTRAL_SRC_EXPRESSION_EVALUATION_BOOLEAN_OPERATION_PART_H_
