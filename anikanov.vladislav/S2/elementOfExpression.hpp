#ifndef ELEMENTOFEXPRESSION_HPP
#define ELEMENTOFEXPRESSION_HPP

#include <iosfwd>
#include <string>

namespace anikanov {
  class ElementOfExpression {
  public:
    virtual ~ElementOfExpression() = default;
    virtual bool isBracket() const noexcept = 0;
    virtual bool isNumber() const noexcept = 0;
    virtual bool isOperation() const noexcept = 0;
  };
}

#endif
