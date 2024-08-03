#include "typization.hpp"
#include <limits>
#include <cmath>

khoroshkin::Operator::Operator() :
  operation('0')
{}

khoroshkin::Operator::Operator(char oper) :
  operation(oper)
{}

khoroshkin::Operand::Operand() :
  value(0)
{}

khoroshkin::Operand::Operand(long long oper) :
  value(oper)
{}

void khoroshkin::Postfix::popOperation()
{
  Operand secondOperand = operands.top();
  operands.pop();
  Operand firstOperand = operands.top();
  operands.pop();
  Operand limitTop = std::numeric_limits< long long >::max();
  Operand limitBottom = std::numeric_limits< long long >::min();

  if (operations.top() == '+')
  {
    if ((limitTop - firstOperand) < secondOperand)
    {
      throw std::logic_error("Error: overflow!");
    }
    operands.push(firstOperand + secondOperand);
  }
  else if (operations.top() == '-')
  {
    if ((limitBottom + secondOperand) > firstOperand)
    {
      throw std::logic_error("Error: overflow!");
    }
    operands.push(firstOperand - secondOperand);
  }
  else if (operations.top() == '*')
  {
    if ((limitTop / secondOperand) < firstOperand || ((limitBottom / secondOperand) > firstOperand))
    {
      throw std::logic_error("Error: overflow!");
    }
    operands.push(firstOperand * secondOperand);
  }
  else if (operations.top() == '/')
  {
    if ((limitBottom / secondOperand) > firstOperand)
    {
      throw std::logic_error("Error: overflow!");
    }
    operands.push(firstOperand / secondOperand);
  }
  else if (operations.top() == '%')
  {
    if (firstOperand < 0)
    {
      operands.push(secondOperand + (firstOperand % secondOperand));
    }
    else
    {
      operands.push(firstOperand % secondOperand);
    }
  }
  operations.pop();
}

bool khoroshkin::Operator::operator==(const char & rhs) const
{
  return operation == rhs;
}

bool khoroshkin::Operator::operator!=(const char & rhs) const
{
  return operation != rhs;
}

khoroshkin::Operand khoroshkin::Operand::operator+(const Operand & rhs)
{
  Operand result;
  result.value = value + rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator-(const Operand & rhs)
{
  Operand result;
  result.value = value - rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator*(const Operand & rhs)
{
  Operand result;
  result.value = value * rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator/(const Operand & rhs)
{
  Operand result;
  result.value = value / rhs.value;
  return result;
}

khoroshkin::Operand khoroshkin::Operand::operator%(const Operand & rhs)
{
  Operand result;
  result.value = value % rhs.value;
  return result;
}

bool khoroshkin::Operand::operator<(const Operand & rhs)
{
  return this->value < rhs.value;
}

bool khoroshkin::Operand::operator>(const Operand & rhs)
{
  return this->value > rhs.value;
}

khoroshkin::Bracket::Bracket(char brack) :
  bracket(brack)
{}

bool khoroshkin::Bracket::isBracket()
{
  return bracket == '(' || bracket == ')';
}

bool khoroshkin::Bracket::isBracketOpen()
{
  return (bracket == '(') ? true : false;
}

bool khoroshkin::Postfix::canPop(Operator oper)
{
  if (operations.isEmpty())
  {
    return false;
  }
  int priorNewOper = oper.getPriority();
  int priorOldOper = operations.top().getPriority();
  return priorNewOper >= 0 && priorOldOper >= 0 && priorNewOper >= priorOldOper;
}

int khoroshkin::Operator::getPriority()
{
  if (operation == '(')
  {
    return -1;
  }
  else if (operation == '*' or operation == '/' or operation == '%')
  {
    return 1;
  }
  else if (operation == '+' or operation == '-')
  {
    return 2;
  }
  throw std::logic_error("Invalid operation");
}
