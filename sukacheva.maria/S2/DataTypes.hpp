#ifndef DATATYPES_HPP
#define DATATYPES_HPP
#include <string>
#include <iosfwd>
#include "Queue.hpp"

namespace sukacheva
{
  struct ElementOfStatement
  {
    ~ElementOfStatement() = default;
    ElementOfStatement() = default;
    ElementOfStatement(std::string applicant_);
    bool isBracket() const noexcept;
    bool isNumber() const noexcept;
    bool isBinaryOperations() const noexcept;
    bool operator==(const char val);

    std::string applicant;
  };

  struct Bracket : public ElementOfStatement
  {
    Bracket(char bracket_);
    Bracket(std::string value);
    bool ifBracketIsOpen() const noexcept;
    bool ifBracketIsClose() const noexcept;

    char bracket;
    ElementOfStatement applicant;
  };

  struct Operand : public ElementOfStatement
  {
    Operand(long long value_);

    long long value;
    ElementOfStatement applicant;
  };

  struct Operation : public ElementOfStatement
  {
    Operation(char operation_);
    Operation(std::string value);

    bool priorityOfOperation(ElementOfStatement other);
    bool operator==(const char val);

    char operation;
    ElementOfStatement applicant;
  };

  struct Postfix
  {
    Queue< ElementOfStatement > postfix;
  };
}

#endif
