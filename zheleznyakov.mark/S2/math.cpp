#include "math.hpp"

void zheleznyakov::processProblems(Stack< std::string > & problems)
{
  while (!problems.empty())
  {
    Queue< std::string > infix;
    Queue< std::string > postfix;
    tokenize(problems.top(), infix);
    infixToPostfix(infix, postfix);
    std::cout << calculatePostfix(postfix) << (problems.size() > 1 ? " " : "");
    problems.pop();
  }
  std::cout << '\n';
}

long long zheleznyakov::calculatePostfix(Queue< std::string > & expression)
{
  Stack < long long > stack;
  while (!expression.empty())
  {
    std::string token = expression.front();
    expression.pop();
    if (isdigit(token[0]))
    {
      stack.push(std::stoll(token));
    }
    else
    {
      long long operand2 = stack.top();
      stack.pop();
      long long operand1 = stack.top();
      stack.pop();
      stack.push(operation(operand1, operand2, token[0]));
    }
  }
  return stack.top();
};

long long zheleznyakov::operation(const long long lval, const long long rval, const char operation)
{
  long long minLimit = std::numeric_limits< long long >::min();
  long long maxLimit = std::numeric_limits< long long >::max();
  if (operation == '+')
  {
    if (maxLimit - lval < rval)
    {
      throw std::overflow_error("Overflow while processing an operation");
    }
    return lval + rval;
  }
  else if (operation == '-')
  {
    if (lval < rval + minLimit)
    {
      throw std::underflow_error("Underflow while processing an operation");
    }
    return lval - rval;
  }
  else if (operation == '*')
  {
    if (maxLimit / lval < rval)
    {
      throw std::overflow_error("Overflow while processing an operation");
    }
    return lval * rval;
  }
  else if (operation == '/')
  {
    return lval / rval;
  }
  else if (operation == '%')
  {
    return lval < 0 ? lval % rval + rval : lval % rval;
  }
  else
  {
    return 0;
  }
}
