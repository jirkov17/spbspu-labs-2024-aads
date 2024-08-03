#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include "Queue.hpp"
#include "Stack.hpp"
#include "IdentifierMath.hpp"

namespace taskaev
{
  void inputMathValue(Queue< IdentifierMath >& queue, std::string mathValue);
  void convertToPostfix(Queue< IdentifierMath >& queue, Queue< IdentifierMath >& postfix, Stack< IdentifierMath >& stack);
  long long calculate(Queue< IdentifierMath >& postfix);
}

#endif
