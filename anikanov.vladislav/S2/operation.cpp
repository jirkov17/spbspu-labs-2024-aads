#include "operation.hpp"

short anikanov::Operation::convertToPriority(std::string op)
{
  if (op == "+" || op == "-") {
    return 1;
  }
  if (op == "*" || op == "/" || op == "%") {
    return 2;
  }
  return 0;
}

anikanov::Operation::Operation(std::string value)
{
  this->value = value;
  priority = convertToPriority(value);
}

bool anikanov::Operation::isBracket() const noexcept
{
  return false;
}

bool anikanov::Operation::isNumber() const noexcept
{
  return false;
}

bool anikanov::Operation::isOperation() const noexcept
{
  return true;
}

short anikanov::Operation::getPriority() const noexcept
{
  return priority;
}

std::string anikanov::Operation::getValue() const noexcept
{
  return value;
}
