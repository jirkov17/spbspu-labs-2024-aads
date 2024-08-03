#include "expressionElement.hpp"

miheev::element_t::element_t():
  type("none")
{}

miheev::element_t::element_t(const element_t& rhs)
{
  *this = rhs;
}

const miheev::Operand& miheev::element_t::getOperand() const
{
  return operand;
}
const miheev::Operation& miheev::element_t::getOperation() const
{
  return operation;
}
const miheev::Parenthesis& miheev::element_t::getParenthesis() const
{
  return parenthesis;
}
const std::string miheev::element_t::getType() const
{
  return type;
}

void miheev::element_t::setOperand(const miheev::Operand& rhs)
{
  operand = rhs;
  type = "operand";
}
void miheev::element_t::setOperand(long long value)
{
  operand.setValue(value);
  type = "operand";
}
void miheev::element_t::setOperation(const miheev::Operation& rhs)
{
  operation = rhs;
  type = "operation";
}
void miheev::element_t::setOperation(char op)
{
  operation.setOperation(op);
  type = "operation";
}
void miheev::element_t::setParenthesis(const miheev::Parenthesis& rhs)
{
  parenthesis = rhs;
  type = "parenthesis";
}
void miheev::element_t::setParenthesis(char par)
{
  parenthesis.parenthesis = par;
  type = "parenthesis";
}


miheev::element_t& miheev::element_t::operator=(const element_t& rhs)
{
  type = rhs.type;
  if (rhs.type == "operation")
  {
    operation = Operation(rhs.operation.getOperation());
  }
  else if (rhs.type == "operand")
  {
    operand = Operand(rhs.operand.getValue());
  }
  else if (rhs.type == "parenthesis")
  {
    parenthesis = Parenthesis{rhs.parenthesis.parenthesis};
  }
  return *this;
}
