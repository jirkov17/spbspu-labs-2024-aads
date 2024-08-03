#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <stdexcept>
#include "ExpressionItem.hpp"

namespace zhitnyj {
  class Operator : public ExpressionItem
  {
  public:
    explicit Operator(char op);
    ~Operator() = default;

    bool isLeftParenthesis() const;
    bool isRightParenthesis() const;
    char getOperator() const;
    int precedence() const;
    long long applyOp(long long a, long long b) const;
    static bool isOperator(char c);

    bool isOperator() override;
    bool isOperand() override;

  private:
    char operator_;
  };
}

#endif
