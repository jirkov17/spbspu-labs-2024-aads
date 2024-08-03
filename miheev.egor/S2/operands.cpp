#include "operands.hpp"
#include <stdexcept>
#include <limits>

miheev::Operand::Operand(long long val):
  value_(val)
{}

void miheev::Operand::setValue(long long val)
{
  value_ = val;
}

long long miheev::Operand::getValue() const
{
  return value_;
}

miheev::Operand miheev::Operand::operator+(const miheev::Operand& rhs) const
{
  bool overflowIsPossible = value_ > 0 && rhs.value_ > 0;
  bool isOverflow = std::numeric_limits< long long >::max() - value_ < rhs.value_;
  if ( overflowIsPossible && isOverflow)
  {
    throw std::logic_error("plus op has overflow\n");
  }
  bool underflowIsPossible = value_ < 0 && rhs.value_ < 0;
  bool isUnderflow = std::numeric_limits< long long >::min() - value_ > rhs.value_;
  if (underflowIsPossible && isUnderflow)
  {
    throw std::logic_error("plus op has underflow\n");
  }
  return miheev::Operand(value_ + rhs.value_);
}
miheev::Operand miheev::Operand::operator-(const miheev::Operand& rhs) const
{
  bool underflowIsPossible = value_ < 0 && rhs.value_ > 0;
  bool isUnderflow = std::numeric_limits< long long >::min() - value_ > -rhs.value_;
  if ( underflowIsPossible && isUnderflow)
  {
    throw std::logic_error("minus op has underflow\n");
  }
  bool overflowIsPossbile = value_ > 0 && rhs.value_ < 0;
  bool isOverflow = std::numeric_limits< long long >::max() + value_ < -rhs.value_;
  if (overflowIsPossbile && isOverflow)
  {
    throw std::logic_error("minus op has overflow\n");
  }
  return miheev::Operand(value_ - rhs.value_);
}
miheev::Operand miheev::Operand::operator*(const miheev::Operand& rhs) const
{
  bool areSameSign = (value_ > 0 && rhs.value_ > 0) || (value_ < 0 && rhs.value_ < 0);
  bool isOverflow = std::numeric_limits< long long >::max() / std::abs(value_) < std::abs(rhs.value_);
  if (areSameSign && isOverflow)
  {
    throw std::logic_error("multiply op has overflow\n");
  }
  bool isUnderflow = std::abs(std::numeric_limits< long long >::min() / value_) < std::abs(rhs.value_);
  if (!areSameSign && isUnderflow)
  {
    throw std::logic_error("multiply op has underflow\n");
  }
  return miheev::Operand(value_ * rhs.value_);
}
miheev::Operand miheev::Operand::operator/(const miheev::Operand& rhs) const
{
  if (rhs.value_ == 0)
  {
    throw std::logic_error("zero division error\n");
  }
  return miheev::Operand(value_ / rhs.value_);
}
miheev::Operand miheev::Operand::operator%(const miheev::Operand& rhs) const
{
  return miheev::Operand((value_ % rhs.value_ + rhs.value_) % rhs.value_);
}
