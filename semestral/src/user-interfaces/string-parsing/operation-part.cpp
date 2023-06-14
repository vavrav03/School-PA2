#include "operation-part.h"

using namespace std;

vector<unique_ptr<OperationPart> > createPostfixFromInfix(vector<unique_ptr<OperationPart> > && infix) {
  vector<unique_ptr<OperationPart> > postfix;
  stack<unique_ptr<OperationPart> > stack;
  for(size_t i = 0; i < infix.size(); i++) {
    if (infix[i]->type == OperationPartType::OPERAND) {
      postfix.push_back(std::move(infix[i]));
    } else if (infix[i]->type == OperationPartType::LEFT_BRACKET) {
      stack.push(std::move(infix[i]));
    } else if (infix[i]->type == OperationPartType::RIGHT_BRACKET) {
      bool bracketMatched = false;
      while (!stack.empty()) {
        if (stack.top()->type == OperationPartType::LEFT_BRACKET) {
          bracketMatched = true;
          stack.pop();
          break;
        } else {
          postfix.push_back(std::move(stack.top()));
          stack.pop();
        }
      }
      if (!bracketMatched) { // stack is empty now
        throw invalid_argument("Mismatched parentheses");
      }
    } else {
      while (!stack.empty() &&
          stack.top()->type != OperationPartType::LEFT_BRACKET &&
          stack.top()->type != OperationPartType::RIGHT_BRACKET &&
          stack.top()->priority >= infix[i]->priority) {
        postfix.push_back(std::move(stack.top()));
        stack.pop();
      }
      stack.push(std::move(infix[i]));
    }
  }
  while (!stack.empty()) {
    if (stack.top()->type == OperationPartType::LEFT_BRACKET
        || stack.top()->type == OperationPartType::RIGHT_BRACKET) {
      throw invalid_argument("Mismatched parentheses");
    }
    postfix.push_back(std::move(stack.top()));
    stack.pop();
  }
  return postfix;
}