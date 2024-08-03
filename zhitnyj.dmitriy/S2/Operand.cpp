#include "Operand.hpp"

zhitnyj::Operand::Operand(long long val) : value(val)
{}

long long zhitnyj::Operand::getValue()
{
  return value;
}

bool zhitnyj::Operand::isOperator()
{
  return false;
}

bool zhitnyj::Operand::isOperand()
{
  return true;
}
