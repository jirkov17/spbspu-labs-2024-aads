#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "stack.hpp"
#include "queue.hpp"
#include "dataTypes.hpp"

namespace nikiforov
{
  std::string cutElements(std::string& str);

  void convertToPostfix(std::string str, Queue< Initialization >& Queue);

  void calculation(Queue< Initialization >& Postfix, Stack< long long >& Result);

  void operations(Initialization operand, Stack< long long >& stack);

  size_t calculationPriority(Initialization elemSeq);
}

#endif
