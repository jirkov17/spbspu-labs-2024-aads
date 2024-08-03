#ifndef ElementStructs_hpp
#define ElementStructs_hpp
#include <string>
#include "Queue.hpp"

namespace reznikova
{
  struct Operator
  {
    Operator(): operator_() {}
    Operator(char value): operator_(value) {}
    char operator_;
  };

  struct Operand
  {
    Operand(): operand_() {}
    Operand(std::string value):
      operand_(0)
    {
      operand_ = std::stoll(value);
    }
    Operand(long long int value): operand_(value) {}
    Operand operator*(const Operand & other);
    Operand operator/(const Operand & other);
    Operand operator+(const Operand & other);
    Operand operator-(const Operand & other);
    Operand operator%(const Operand & other);
    long long int operand_;
  };

  struct Bracket
  {
    Bracket(): bracket_() {}
    Bracket(char value): bracket_(value) {}
    char bracket_;
  };

  enum type_t
  {
    operand_type,
    operator_type,
    open_bracket_type,
    close_bracket_type,
    else_
  };

  struct Element
  {
    Element();
    Element(const Element & other);
    type_t & getType();
    Operator & getOperator();
    Operand & getOperand();
    Bracket & getOpenBracket();
    Bracket & getCloseBracket();
    union elem_t
    {
      elem_t() {}
      elem_t(const elem_t & other)
      {
        operand_ = other.operand_;
        operator_ = other.operator_;
        open_bracket_ = other.open_bracket_;
        close_bracket_ = other.close_bracket_;
      }
      ~elem_t() {}
      Operand operand_;
      Operator operator_;
      Bracket open_bracket_;
      Bracket close_bracket_;
    };
    elem_t elem_;
    type_t types_;
  };

  struct Postfix
  {
    Queue< Element > postfix_;
  };

}

#endif
