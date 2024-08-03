#ifndef TYPES_HPP
#define TYPES_HPP
#include "stack.hpp"

namespace mihalchenko
{
  struct Operand
  {
    Operand() = default;
    Operand(long long data);
    Operand operator+(const Operand &rhs);
    Operand operator-(const Operand &rhs);
    Operand operator*(const Operand &rhs);
    Operand operator/(const Operand &rhs);
    Operand operator%(const Operand &rhs);
    long long data_;
  };

  struct Operation
  {
  public:
    Operation() = default;
    explicit Operation(char command);
    bool operator==(const Operation &rhs) const;
    bool operator<(const Operation &rhs) const;
    bool operator>(const Operation &rhs) const;
    void setOperation(const char command);
    char getOperation() const;

  private:
    char command_;
    short weightOfCommand_;
  };

  struct Parenthesis
  {
    char parenthesis;
  };

  struct FinalTransform
  {
    bool calculate();
    Stack< Operand > calcRezult;
    Stack< Operation > compRez;
    Stack< char > commands;
  };
}

#endif
