#include "./relational-operation-factories.h"

using namespace std;

VariableOperandFactory::VariableOperandFactory(VariablesMemory &memory)
    : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

bool VariableOperandFactory::canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const {
  if (tokens[nextTokenIndex].quoted) {
    return true;
  }
  return !Tokenizer::getInstnace().isSpecialCharacter(tokens[nextTokenIndex].value);
}

std::unique_ptr<OperationPart<AbstractDataSource> > VariableOperandFactory::create(const std::vector<Token> &tokens,
                                                                                   size_t &nextTokenIndex) const {
  if (!memory.exists(tokens[nextTokenIndex].value)) {
    throw std::runtime_error("Variable " + tokens[nextTokenIndex].value + " does not exist.");
  }
  std::unique_ptr<OperationPart<AbstractDataSource> >
      returnValue = std::make_unique<VariableOperand>(memory.get(tokens[nextTokenIndex].value));
  nextTokenIndex++;
  return returnValue;
}

CSVOperandFactory::CSVOperandFactory(VariablesMemory &memory)
    : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

bool CSVOperandFactory::canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const {
  return tokens[nextTokenIndex].quoted && getExtensionFromPath(tokens[nextTokenIndex].value) == "csv";
}

std::unique_ptr<OperationPart<AbstractDataSource> > CSVOperandFactory::create(const std::vector<Token> &tokens,
                                                                              size_t &nextTokenIndex) const {
  std::string path = tokens[nextTokenIndex].value;
  auto returnValue = std::make_unique<CSVOperand>(path);
  nextTokenIndex++;
  return returnValue;
}

JSONOperandFactory::JSONOperandFactory(VariablesMemory &memory)
    : OperationPartFactory<AbstractDataSource>(), memory(memory) {}

bool JSONOperandFactory::canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const {
  return tokens[nextTokenIndex].quoted && getExtensionFromPath(tokens[nextTokenIndex].value) == "json";
}

std::unique_ptr<OperationPart<AbstractDataSource> > JSONOperandFactory::create(const std::vector<Token> &tokens,
                                                                               size_t &nextTokenIndex) const {
  std::string path = tokens[nextTokenIndex].value;
  auto returnValue = std::make_unique<JSONOperand>(path);
  nextTokenIndex++;
  return returnValue;
}
