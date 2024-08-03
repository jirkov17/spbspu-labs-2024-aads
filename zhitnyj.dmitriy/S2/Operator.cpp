#include "Operator.hpp"

zhitnyj::Operator::Operator(char op) : operator_(op)
{
  if (!isOperator(op))
  {
    throw std::invalid_argument("Unsupported operator");
  }
}

bool zhitnyj::Operator::isLeftParenthesis() const
{
  return operator_ == '(';
}

bool zhitnyj::Operator::isRightParenthesis() const
{
  return operator_ == ')';
}

char zhitnyj::Operator::getOperator() const
{
  return operator_;
}

int zhitnyj::Operator::precedence() const
{
  if (operator_ == '+' || operator_ == '-')
  {
    return 1;
  }
  else if (operator_ == '*' || operator_ == '/' || operator_ == '%')
  {
    return 2;
  }
  else if (operator_ == '(' || operator_ == ')')
  {
    return 0;
  }
  else
  {
    throw std::runtime_error("Unsupported operator");
  }
}

long long zhitnyj::Operator::applyOp(long long a, long long b) const
{
  if (operator_ == '+')
  {
    return a + b;
  }
  else if (operator_ == '-')
  {
    return a - b;
  }
  else if (operator_ == '*')
  {
    return a * b;
  }
  else if (operator_ == '/')
  {
    if (b == 0)
    {
      throw std::runtime_error("Division by zero");
    }
    return a / b;
  }
  else if (operator_ == '%')
  {
    if (b == 0)
    {
      throw std::runtime_error("Modulo by zero");
    }
    if (a < 0)
    {
      return a % b + abs(b);
    }
    return a % b;
  }
  else
  {
    throw std::invalid_argument("Invalid operation");
  }
}

bool zhitnyj::Operator::isOperator()
{
  return true;
}

bool zhitnyj::Operator::isOperand()
{
  return false;
}

bool zhitnyj::Operator::isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')';
}

