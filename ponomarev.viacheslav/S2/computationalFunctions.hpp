#ifndef COMPUTATIONAL_FUNCTIONS_HPP
#define COMPUTATIONAL_FUNCTIONS_HPP

#include <string>
#include "typing.hpp"

namespace ponomarev
{
  void getPostfix(std::string expression, Postfix & postfix);

  bool isNum(const std::string & str);
  bool isOpenBracketUp(const Stack< ExpressionElement > & stack);
  bool shouldPushOpToStack(const Stack< ExpressionElement > & stack, const ExpressionElement & elem);

  ExpressionElement getElem(std::string & expression);
  long long calculate(std::string & expression);
}

#endif
