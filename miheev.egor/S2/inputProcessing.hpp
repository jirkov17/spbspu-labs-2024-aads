#ifndef INPUT_PROCESSING_HPP
#define INPUT_PROCESSING_HPP

#include <ios>
#include "stack.hpp"
#include "queue.hpp"
#include "expressionElement.hpp"

namespace miheev
{
  Stack< long long > processInput(std::istream&);
}

#endif
