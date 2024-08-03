#include "dataTypes.hpp"
#include <stdexcept>

nikiforov::Initialization::Initialization(std::string& str)
{
  if (isdigit(str[0]))
  {
    type = operand;
    operand_.data = std::stoll(str);
  }
  else if (isOperation(str))
  {
    type = operation;
    operation_.data = str[0];
  }
  else if (str == "(")
  {
    type = openBracket;
    bracket_.data = str[0];
  }
  else
  {
    type = closeBracket;
    bracket_.data = str[0];
  }
}

bool nikiforov::Initialization::isOperation(std::string str)
{
  return (str == "+" || str == "-" || str == "*" || str == "/" || str == "%");
}
