#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <string>
#include "stack.hpp"

namespace khoroshkin
{
  void inputInfix(std::istream & in, Stack< std::string > & expressions);
  long long calculateExpression(const std::string & str);
  std::string getToken(const std::string & str, size_t & pos);
  std::string readOperand(const std::string & str, size_t & pos);
  char readOperation(const std::string & str, size_t & pos);
  void skipWhitespace(const std::string & str, size_t & pos);
  bool isDigit(const std::string & str);
}

#endif
