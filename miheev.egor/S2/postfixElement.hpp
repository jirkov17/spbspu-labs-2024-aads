#ifndef POSTFIX_ELEMENT_HPP
#define POSTFIX_ELEMENT_HPP

#include "expressionElement.hpp"

namespace miheev
{
  struct postfix_t
  {
  public:
    postfix_t();
    postfix_t(const postfix_t&);
    explicit postfix_t(const element_t&);
    postfix_t& operator=(const postfix_t&);

    const Operand& getOperand() const;
    const Operation& getOperation() const;
    const std::string getType() const;

    void setOperand(const Operand& rhs);
    void setOperation(const Operation& rhs);

  private:
    Operand operand;
    Operation operation;
    std::string type;
  };
}

#endif
