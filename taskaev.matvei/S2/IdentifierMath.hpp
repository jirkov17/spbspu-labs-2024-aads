#ifndef IDENTIFIERMATH_HPP
#define IDENTIFIERMATH_HPP
#include <stdexcept>
#include <string>
#include <cstring>

namespace taskaev
{
  enum mathType
  {
    operand,
    operation,
    openParantheses,
    closedParantheses
  };

  struct Operand
  {
    long long data;
  };

  struct Operation
  {
    char data;
  };

  struct IdentifierMath {
    mathType types;
    union
    {
      Operand operands;
      Operation operations;
      char parantheses;
    };
    IdentifierMath() = default;
    explicit IdentifierMath(const std::string& item);
    private:
      bool isValue(const std::string& item);
      bool isOperation(char c);
  };
}

#endif
