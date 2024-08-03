#ifndef BRACKET_HPP
#define BRACKET_HPP

#include "elementOfExpression.hpp"

namespace anikanov {
  class Bracket : public ElementOfExpression {
  public:
    Bracket() = default;
    explicit Bracket(std::string value);
    bool isBracket() const noexcept override;
    bool isForward() const noexcept;
    bool isBackward() const noexcept;
    bool isNumber() const noexcept override;
    bool isOperation() const noexcept override;
  private:
    short priority{};
    std::string value{};
  };
}

#endif
