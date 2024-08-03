#ifndef OPERANDS_HPP
#define OPERANDS_HPP

namespace miheev
{
  class Operand
  {
  public:
    Operand() = default;
    explicit Operand(long long val);

    void setValue(long long);
    long long getValue() const;

    Operand operator+(const Operand& rhs) const;
    Operand operator-(const Operand& rhs) const;
    Operand operator*(const Operand& rhs) const;
    Operand operator/(const Operand& rhs) const;
    Operand operator%(const Operand& rhs) const;
  private:
    long long value_;
  };
}


#endif
