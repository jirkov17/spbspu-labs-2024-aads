#include "ElementStructs.hpp"

reznikova::Operand reznikova::Operand::operator*(const reznikova::Operand & other)
{
  return Operand(operand_ * other.operand_);
}

reznikova::Operand reznikova::Operand::operator/(const reznikova::Operand & other)
{
  return Operand(operand_ / other.operand_);
}

reznikova::Operand reznikova::Operand::operator+(const reznikova::Operand & other)
{
  return Operand(operand_ + other.operand_);
}

reznikova::Operand reznikova::Operand::operator-(const reznikova::Operand & other)
{
  return Operand(operand_ - other.operand_);
}

reznikova::Operand reznikova::Operand::operator%(const reznikova::Operand & other)
{
  return Operand(operand_ % other.operand_);
}

reznikova::Element::Element():
  elem_(),
  types_(else_)
{}

reznikova::Element::Element(const Element & other):
  elem_(other.elem_),
  types_(other.types_)
{}

reznikova::type_t & reznikova::Element::getType()
{
  return types_;
}

reznikova::Operator & reznikova::Element::getOperator()
{
    return elem_.operator_;
}

reznikova::Operand & reznikova::Element::getOperand()
{
    return elem_.operand_;
}

reznikova::Bracket & reznikova::Element::getOpenBracket()
{
    return elem_.open_bracket_;
}

reznikova::Bracket & reznikova::Element::getCloseBracket()
{
  return elem_.close_bracket_;
}
