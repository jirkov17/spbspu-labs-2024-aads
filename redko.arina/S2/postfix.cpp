#include "postfix.hpp"
#include "stack.hpp"

long long redko::Postfix::calculate()
{
  Stack< Operand > calc{};
  Operand rOperand{};
  Operand lOperand{};

  while (!postfix.empty())
  {
    if (postfix.front().type == operand)
    {
      calc.push(postfix.front().elem.operand);
    }
    else if (calc.size() > 1)
    {
      rOperand = calc.top();
      calc.pop();
      lOperand = calc.top();
      calc.pop();
      if (postfix.front().elem.operation.operation == '+')
      {
        calc.push(lOperand + rOperand);
      }
      else if (postfix.front().elem.operation.operation == '-')
      {
        calc.push(lOperand - rOperand);
      }
      else if (postfix.front().elem.operation.operation == '*')
      {
        calc.push(lOperand * rOperand);
      }
      else if (postfix.front().elem.operation.operation == '/')
      {
        calc.push(lOperand / rOperand);
      }
      else
      {
        calc.push(lOperand % rOperand);
      }
    }
    else
    {
      throw std::invalid_argument("Error: wrong expression");
    }
    postfix.pop();
  }
  return calc.top().value;
}
