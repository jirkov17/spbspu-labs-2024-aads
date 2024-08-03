#ifndef OPERAND_HPP
#define OPERAND_HPP

#include "elementOfExpression.hpp"

namespace anikanov {
  class Operand : public ElementOfExpression {
  public:
    Operand() = default;
    explicit Operand(long long value);
    explicit Operand(std::string value);
    bool isBracket() const noexcept override;
    bool isNumber() const noexcept override;
    bool isOperation() const noexcept override;
    long long getValue() const;
  private:
    long long value{};
  };
}

#endif
