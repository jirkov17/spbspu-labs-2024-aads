#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>
#include <memory>
#include "stack.hpp"

namespace sobolevsky
{
  void fillStack(std::istream & in, Stack< std::string > & expressions);
  bool isDigit(std::string c);
  int algebrChars(std::string c);
  long long counter(std::string ch, long long first, long long second);
  std::shared_ptr< std::string[] > fromInfixToPostfix(std::string infixExpression, long long &i);
  long long countPostfix(std::shared_ptr< std::string[] > postfix, long long length);
}

#endif
