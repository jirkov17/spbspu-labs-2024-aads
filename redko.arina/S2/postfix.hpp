#ifndef POSTFIX_HPP
#define POSTFIX_HPP
#include "expressionTypes.hpp"

namespace redko
{
  struct Postfix
  {
    long long calculate();

    Queue< PostfixElem > postfix;
  };
}

#endif
