#include "./relational-operation-factories.h"

using namespace std;

ProjectionOperatorFactory::ProjectionOperatorFactory() : OperationPartFactory() {}

bool ProjectionOperatorFactory::canCreate(const std::vector<Token> &tokens, size_t nextTokenIndex) const {
  if (tokens[nextTokenIndex].value != "[") {
    return false;
  }
  bool lastWasSpecial = false;
  for (size_t i = nextTokenIndex + 1; i < tokens.size(); i++) {
    if (tokens[i].value == "]") {
      return i != nextTokenIndex + 1; // empty projection is not allowed
    } else if (tokens[i].value == "[") {
      return false;
    } else if (tokens[i].value == "-") {
      if (lastWasSpecial) {
        return false;
      }
      if (i + 1 == tokens.size() || tokens[i + 1].value != ">") {
        return false;
      }
      i++;
      lastWasSpecial = true;
    } else if (tokens[i].value == ",") {
      if (lastWasSpecial) {
        return false;
      }
      lastWasSpecial = true;
    } else if (Tokenizer::getInstnace().isSpecialCharacter(tokens[i].value)) {
      return false;
    } else {
      lastWasSpecial = false;
    }
  }
  return false; // no ]
}

unique_ptr<OperationPart<AbstractDataSource> >
ProjectionOperatorFactory::create(const std::vector<Token> &tokens, size_t &nextTokenIndex) const {
  vector<string> header;
  unordered_map<string, string> aliasToOldName;
  nextTokenIndex++; // skip [
  while (nextTokenIndex < tokens.size()) {
    if (tokens[nextTokenIndex].value == "]") {
      nextTokenIndex++;
      break;
    } else if (tokens[nextTokenIndex].value == ",") {
      nextTokenIndex++;
      continue;
    } else if (tokens[nextTokenIndex + 1].value == "-") { // old(currentIndex) -> alias
      aliasToOldName[tokens[nextTokenIndex + 3].value] = tokens[nextTokenIndex].value;
      header.push_back(tokens[nextTokenIndex + 3].value);
      nextTokenIndex += 4;
    } else {
      header.push_back(tokens[nextTokenIndex].value);
      nextTokenIndex++;
    }
  }
  return make_unique<ProjectionOperator>(header, aliasToOldName);
}