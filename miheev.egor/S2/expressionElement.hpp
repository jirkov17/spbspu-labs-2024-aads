#ifndef EXPRESSION_ELEMENT_HPP
#define EXPRESSION_ELEMENT_HPP

#include "operations.hpp"
#include "operands.hpp"
#include "string"

namespace miheev
{
  struct element_t
  {
  public:
    element_t();
    element_t(const element_t&);
    element_t& operator=(const element_t&);

    const Operand& getOperand() const;
    const Operation& getOperation() const;
    const Parenthesis& getParenthesis() const;
    const std::string getType() const;

    void setOperand(const Operand& rhs);
    void setOperand(long long);
    void setOperation(const Operation& rhs);
    void setOperation(char);
    void setParenthesis(const Parenthesis& rhs);
    void setParenthesis(char);

  private:
    Operand operand;
    Operation operation;
    Parenthesis parenthesis;
    std::string type;
  };
}

#endif
