#ifndef PROCESSINGFUNCTIONS_HPP
#define PROCESSINGFUNCTIONS_HPP
#include <istream>
#include "stack.hpp"
#include "expressionTypes.hpp"

namespace redko
{
  bool isNumeric(const std::string & str);
  ExprElem cutElem(std::string & str);
  void processExpressions(std::istream & input, Stack< long long > & res);
}

#endif
