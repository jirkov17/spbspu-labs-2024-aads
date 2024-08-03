#ifndef TERMFUNCS_HPP
#define TERMFUNCS_HPP
#include <string>
#include <iostream>
#include "queue.hpp"
#include "stack.hpp"

namespace psarev
{
  bool checkOperand(std::string symbol);
  bool checkOperator(std::string c);
  int priori(std::string c);

  void readTerms(std::istream& input, Queue< std::string >& result);
  void makeQueue(std::string expression, Queue< std::string >& result);
  void postfixation(Queue< std::string >& term, Queue< std::string >& result);
  long long makeOperation(long long first, long long second, std::string operation);
  long long calculateTerm(Queue< std::string >& terms);

  void makeResults(Queue< std::string >& terms, Stack< long long >& results);
}

#endif
