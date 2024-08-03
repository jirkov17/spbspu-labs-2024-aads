#include "IdentifierMath.hpp"

namespace taskaev
{
  IdentifierMath::IdentifierMath(const std::string& item)
  {
    if (!isValue(item))
    {
      throw std::invalid_argument(" SOS are you Ok?");
    }
    if (isdigit(item[0]))
    {
      types = operand;
      operands.data = std::stoll(item);
    }
    else if (isOperation(item[0]))
    {
      types = operation;
      operations.data = item[0];
    }
    else if ('(' == item[0])
    {
      types = openParantheses;
      parantheses = item[0];
    }
    else
    {
      types = closedParantheses;
      parantheses = item[0];
    }
  }
  bool IdentifierMath::isValue(const std::string& item)
  {
    for (size_t i = 0; i < item.length(); i++)
    {
      if (!isdigit(item[i]) && (item.length() > 1))
      {
        return false;
      }
    }
    return true;
  }
  bool IdentifierMath::isOperation(char c)
  {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
  }
}

