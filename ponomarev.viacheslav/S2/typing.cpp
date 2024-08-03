#include "typing.hpp"
#include <limits>

ponomarev::Bracket::Bracket(char symbol):
  bracket_(symbol)
{}

ponomarev::Operand::Operand():
  num_(0)
{}

ponomarev::Operand::Operand(long long num):
  num_(num)
{}

void ponomarev::Operand::putValue(long long value)
{
  num_ = value;
}

long long ponomarev::Operand::getValue()
{
  return num_;
}

ponomarev::Operation::Operation(char symbol):
  operation_(symbol)
{
  if (symbol == '+' || symbol == '-')
  {
    priority_ = 1;
  }
  else if (symbol == '*' || symbol == '/')
  {
    priority_ = 2;
  }
  else
  {
    priority_ = 0;
  }
}

void ponomarev::Operation::putOperation(char symbol)
{
  operation_ = symbol;
}

ponomarev::Operand ponomarev::Operation::useOperation(const Operand left, const Operand right) const
{
  Operand res;
  long long first = left.num_;
  long long second = right.num_;

  if (operation_ == '+')
  {
    if ((std::numeric_limits< long long >::max() - first) < second)
    {
      throw std::overflow_error("overflow error");
    }
    res.num_ = first + second;
    return res;
  }
  else if (operation_ == '-')
  {
    if (first < (std::numeric_limits< long long >::min() + second))
    {
      throw std::overflow_error("underflow error");
    }
    res.num_ = first - second;
    return res;
  }
  else if (operation_ == '*')
  {
    if ((std::numeric_limits< long long >::max() / first) < second)
    {
      throw std::overflow_error("overflow error");
    }
    res.num_ = first * second;
    return res;
  }
  else if (operation_ == '/')
  {
    res.num_ = first / second;
    return res;
  }
  else if (operation_ == '%')
  {
    res.num_ = first < 0 ? (first % second + second) : first % second;
    return res;
  }
  else
  {
    throw std::logic_error("Unsupported operation");
  }
}

ponomarev::ExpressionElement::ExpressionElement():
  type("none"),
  bracket('a'),
  operation('+'),
  operand(0)
{}

void ponomarev::ExpressionElement::putOperand(long long value)
{
  operand.putValue(value);
  type = "Operand";
}

void ponomarev::ExpressionElement::putOperation(char symbol)
{
  operation.putOperation(symbol);
  type = "Operation";
}

void ponomarev::ExpressionElement::putBracket(char symbol)
{
  bracket.bracket_ = symbol;
  type = "Bracket";
}

const std::string ponomarev::ExpressionElement::getType() const
{
  return type;
}

const ponomarev::Operand & ponomarev::ExpressionElement::getOperand() const
{
  return operand;
}
const ponomarev::Operation & ponomarev::ExpressionElement::getOperation() const
{
  return operation;
}
const ponomarev::Bracket & ponomarev::ExpressionElement::getBracket() const
{
  return bracket;
}
