#include "DataTypes.hpp"
#include <string>

sukacheva::Bracket::Bracket(char bracket_):
  ElementOfStatement(std::string(1, bracket_)),
  bracket(bracket_)
{}

sukacheva::Bracket::Bracket(std::string value):
  ElementOfStatement(value),
  bracket(*value.c_str())
{}

bool sukacheva::Bracket::ifBracketIsOpen() const noexcept
{
  return bracket == '(';
}

bool sukacheva::Bracket::ifBracketIsClose() const noexcept
{
  return bracket == ')';
}

sukacheva::Operand::Operand(long long value_):
  ElementOfStatement(std::to_string(value_)),
  value(value_)
{}

sukacheva::Operation::Operation(char operation_) :
  ElementOfStatement(std::string(1, operation_)),
  operation(operation_)
{}

sukacheva::Operation::Operation(std::string value):
  ElementOfStatement(value),
  operation(*value.c_str())
{}

bool sukacheva::Operation::priorityOfOperation(ElementOfStatement other)
{
  int priorityIndex1 = 1;
  int priorityIndex2 = 1;
  if (other.applicant == "*" || other.applicant == "/" || other.applicant == "%")
  {
    priorityIndex1 = 2;
  }
  if (operation == '*' || operation == '/' || operation == '%')
  {
    priorityIndex2 = 2;
  }
  else if (operation == '(' || other.applicant == "(")
  {
    return false;
  }
  return priorityIndex1 >= priorityIndex2;
}

sukacheva::ElementOfStatement::ElementOfStatement(std::string applicant_):
  applicant(applicant_)
{}

bool sukacheva::ElementOfStatement::isBracket() const noexcept
{
  return applicant == "(" || applicant == ")";
}

bool sukacheva::ElementOfStatement::isNumber() const noexcept
{
  return !applicant.empty() && (applicant.find_first_not_of("0123456789") == applicant.npos);
}

bool sukacheva::ElementOfStatement::isBinaryOperations() const noexcept
{
  return !applicant.empty() && (applicant.find_first_not_of("+-*/%") == applicant.npos);
}

bool sukacheva::Operation::operator==(const char val)
{
  return operation == val;
}

bool sukacheva::ElementOfStatement::operator==(const char val)
{
  if (isBinaryOperations())
  {
    Operation op = applicant;
    return op == val;
  }
  else
  {
    return applicant[0] == val;
  }
}
