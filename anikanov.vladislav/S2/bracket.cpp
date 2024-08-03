#include "bracket.hpp"

anikanov::Bracket::Bracket(std::string value)
{
  this->value = value;
  priority = 0;
}

bool anikanov::Bracket::isBracket() const noexcept
{
  return true;
}

bool anikanov::Bracket::isForward() const noexcept
{
  if (value == "(") {
    return true;
  }
  return false;
}

bool anikanov::Bracket::isBackward() const noexcept
{
  if (value == ")") {
    return true;
  }
  return false;
}

bool anikanov::Bracket::isNumber() const noexcept
{
  return false;
}

bool anikanov::Bracket::isOperation() const noexcept
{
  return false;
}
