#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "ExpressionItem.hpp"

namespace zhitnyj {
  class Operand : public ExpressionItem
  {
  public:
    explicit Operand(long long val);
    ~Operand() = default;

    long long getValue();
    bool isOperator() override;
    bool isOperand() override;

  private:
    long long value;
  };
}

#endif
