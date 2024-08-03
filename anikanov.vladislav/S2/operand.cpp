#include "operand.hpp"

#include <string>

anikanov::Operand::Operand(long long int value)
{
  this->value = value;
}

anikanov::Operand::Operand(std::string value)
{
  this->value = std::stoll(value);
}

bool anikanov::Operand::isBracket() const noexcept
{
  return false;
}

bool anikanov::Operand::isNumber() const noexcept
{
  return true;
}

bool anikanov::Operand::isOperation() const noexcept
{
  return false;
}

long long anikanov::Operand::getValue() const
{
  return value;
}
