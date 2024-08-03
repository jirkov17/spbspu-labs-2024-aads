#ifndef MATH_HPP
#define MATH_HPP
#include <fstream>
#include <limits>
#include "queue.hpp"
#include "stack.hpp"
#include "input.hpp"
namespace zheleznyakov
{
  void processProblems(Stack< std::string > & problems);
  long long calculatePostfix(Queue< std::string > & expression);
  long long operation(const long long lval, const long long rval, const char operation);
}
#endif
