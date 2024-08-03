#include "operations.hpp"
#include <stdexcept>

miheev::Operation::Operation(char op):
  operation_(op)
{
  if (op == '+' || op == '-')
  {
    priority_ = 1;
  }
  else if (op == '*' || op == '/')
  {
    priority_ = 2;
  }
  else
  {
    priority_ = 0;
  }
}

bool miheev::Operation::operator<(const miheev::Operation& rhs) const
{
  return priority_ < rhs.priority_;
}

bool miheev::Operation::operator<=(const miheev::Operation& rhs) const
{
  return priority_ <= rhs.priority_;
}

bool miheev::Operation::operator==(const miheev::Operation& rhs) const
{
  return priority_ == rhs.priority_;
}

bool miheev::Operation::operator>=(const miheev::Operation& rhs) const
{
  return priority_ >= rhs.priority_;
}

bool miheev::Operation::operator>(const miheev::Operation& rhs) const
{
  return priority_ > rhs.priority_;
}

miheev::Operand miheev::Operation::implement(const miheev::Operand& lhs, const miheev::Operand& rhs) const
{
  if (operation_ == '+')
  {
    return lhs + rhs;
  }
  else if (operation_ == '-')
  {
    return lhs - rhs;
  }
  else if (operation_ == '*')
  {
    return lhs * rhs;
  }
  else if (operation_ == '/')
  {
    return lhs / rhs;
  }
  else if (operation_ == '%')
  {
    return lhs % rhs;
  }
  else
  {
    throw std::logic_error("Unsupported operation");
  }
}

char miheev::Operation::getOperation() const
{
  return operation_;
}

void miheev::Operation::setOperation(char op)
{
  operation_ = op;
  if (op == '+' || op == '-')
  {
    priority_ = 1;
  }
  else if (op == '*' || op == '/')
  {
    priority_ = 2;
  }
  else
  {
    priority_ = 0;
  }
}
