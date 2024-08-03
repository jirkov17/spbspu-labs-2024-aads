#ifndef OPERATION_HPP
#define OPERATION_HPP

#include "elementOfExpression.hpp"

namespace anikanov {
  class Operation : public ElementOfExpression {
  public:
    Operation() = default;
    explicit Operation(std::string value);
    bool isBracket() const noexcept override;
    bool isNumber() const noexcept override;
    bool isOperation() const noexcept override;
    short getPriority() const noexcept;
    std::string getValue() const noexcept;
  private:
    short convertToPriority(std::string op);

    short priority{};
    std::string value{};
  };
}

#endif
