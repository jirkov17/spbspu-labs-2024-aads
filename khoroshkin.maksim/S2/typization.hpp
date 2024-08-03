#ifndef TYPIZATION_HPP
#define TYPIZATION_HPP

#include "stack.hpp"

namespace khoroshkin
{
  struct Operand
  {
    Operand();
    Operand(long long oper);

    Operand operator+(const Operand & rhs);
    Operand operator-(const Operand & rhs);
    Operand operator*(const Operand & rhs);
    Operand operator/(const Operand & rhs);
    Operand operator%(const Operand & rhs);

    bool operator<(const Operand & rhs);
    bool operator>(const Operand & rhs);

    long long value;
  };

  struct Operator
  {
    Operator();
    Operator(char oper);

    int getPriority();

    bool operator==(const char & rhs) const;
    bool operator!=(const char & rhs) const;

    char operation;
  };

  struct Bracket
  {
    Bracket(char brack);

    bool isBracket();
    bool isBracketOpen();

    char bracket;
  };

  struct Postfix
  {
    void popOperation();
    bool canPop(Operator oper);

    Stack< Operand > operands;
    Stack< Operator > operations;
  };
}

#endif
