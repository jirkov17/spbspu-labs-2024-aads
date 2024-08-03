#ifndef INPUT_FUNCTIONS_HPP
#define INPUT_FUNCTIONS_HPP

#include <ios>
#include <string>
#include "queue.hpp"
#include "stack.hpp"

namespace ponomarev
{
  void inputExpressions(std::istream & input, Queue< std::string > & expressions);
  void getResults(Queue< std::string > & expressions, Stack< long long > & res);
}

#endif
