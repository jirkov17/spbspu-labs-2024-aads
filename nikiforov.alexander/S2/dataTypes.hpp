#ifndef DATATYPES_HPP
#define DATATYPES_HPP
#include <string>

namespace nikiforov
{
  enum Type
  {
    operation,
    operand,
    openBracket,
    closeBracket
  };

  struct Operand
  {
    long long data;
  };

  struct Operation
  {
    char data;
  };

  struct Bracket
  {
    char data;
  };

  class Initialization
  {
  public:
    union
    {
      Operand operand_;
      Operation operation_;
      Bracket bracket_;
    };
    Type type;

    Initialization() = default;
    Initialization(std::string& str);

  private:
    bool isOperation(std::string str);
  };

}

#endif
