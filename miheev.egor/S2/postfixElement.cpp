#include "postfixElement.hpp"

miheev::postfix_t::postfix_t():
  type("none")
{}

miheev::postfix_t::postfix_t(const miheev::postfix_t& rhs)
{
  *this = rhs;
}

miheev::postfix_t::postfix_t(const miheev::element_t& rhs)
{
  type = rhs.getType();
  if (rhs.getType() == "operand")
  {
    operand = rhs.getOperand();
  }
  else if (rhs.getType() == "operation")
  {
    operation = rhs.getOperation();
  }
}

miheev::postfix_t& miheev::postfix_t::operator=(const miheev::postfix_t& rhs)
{
  type = rhs.type;
  if (rhs.type == "operand")
  {
    operand = rhs.operand;
  }
  else if (rhs.type == "operation")
  {
    operation = rhs.operation;
  }
  return *this;
}

const miheev::Operand& miheev::postfix_t::getOperand() const
{
  return operand;
}

const miheev::Operation& miheev::postfix_t::getOperation() const
{
  return operation;
}

const std::string miheev::postfix_t::getType() const
{
  return type;
}

void miheev::postfix_t::setOperand(const miheev::Operand& rhs)
{
  operand.setValue(rhs.getValue());
  type = "operand";
}

void miheev::postfix_t::setOperation(const miheev::Operation& rhs)
{
  operation.setOperation(rhs.getOperation());
  type = "operation";
}
