#include "operation-part.h"

using namespace std;

vector<OperationPart *> createPostfixFromInfix(const std::vector<OperationPart *> &infix) {
  vector<OperationPart *> postfix;
  stack<OperationPart *> stack;
  for (auto &part: infix) {
    if (part->type == OperationPartType::OPERAND) {
      postfix.push_back(part);
    } else if (part->type == OperationPartType::LEFT_BRACKET) {
      stack.push(part);
    } else if (part->type == OperationPartType::RIGHT_BRACKET) {
      bool bracketMatched = false;
      while (!stack.empty()) {
        if (stack.top()->type == OperationPartType::LEFT_BRACKET) {
          bracketMatched = true;
          stack.pop();
          break;
        } else {
          postfix.push_back(stack.top());
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
             stack.top()->priority >= part->priority) {
        postfix.push_back(stack.top());
        stack.pop();
      }
      stack.push(part);
    }
  }
  while (!stack.empty()) {
    if (stack.top()->type == OperationPartType::LEFT_BRACKET
        || stack.top()->type == OperationPartType::RIGHT_BRACKET) {
      throw invalid_argument("Mismatched parentheses");
    }
    postfix.push_back(stack.top());
    stack.pop();
  }
  return postfix;
}