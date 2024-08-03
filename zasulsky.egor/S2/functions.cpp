#include "functions.hpp"
#include <iostream>
#include <string>
#include <climits>
#include <stdexcept>

int zasulsky::getPriority(std::string s)
{
  if (s == "^")
  {
    return 3;
  }

  else if (s == "*" || s == "/")
  {
    return 2;
  }

  else if (s == "+" || s == "-")
  {
    return 1;
  }

  else
  {
    return 0;
  }
}

bool zasulsky::isOperand(std::string st)
{
  for (char s : st)
  {
    if (!isdigit(s))
    {
      return false;
    }
  }
  return true;
}

zasulsky::Queue< std::string > zasulsky::convertToPostfix(zasulsky::Queue< std::string >& infix)
{
  zasulsky::Queue< std::string > postfix;
  zasulsky::Stack< std::string > st;

  while (!infix.isEmpty())
  {
    auto p = infix.peek();
    if (isOperand(p))
    {
      postfix.enqueue(p);
    }

    else if (st.isEmpty())
    {
      st.push(p);
    }

    else if (st.isEmpty())
    {
      st.push(p);
    }

    else if (p == "^")
    {
      st.push(p);
    }

    else if (p == "*" || p == "/")
    {
      while (!st.isEmpty() && 2 <= getPriority(st.top()))
      {
        postfix.enqueue(st.top());
        st.pop();
      }
      st.push(p);
    }
    else if (p == "+" || p == "-" || p == "%")
    {
      while (!st.isEmpty() && 1 <= getPriority(st.top()))
      {
        postfix.enqueue(st.top());
        st.pop();
      }
      st.push(p);
    }
    else if (p == "(")
    {
      st.push(p);
    }
    else if (p == ")")
    {
      while (!st.isEmpty() && st.top() != "(")
      {
        postfix.enqueue(st.top());
        st.pop();
      }
      st.pop();
    }
    infix.dequeue();
  }
  if (infix.isEmpty())
  {
    while (!st.isEmpty())
    {
      postfix.enqueue(st.top());
      st.pop();
    }
  }
  if (postfix.isEmpty())
  {
    throw std::logic_error("the expression contains only parentheses!");
  }
  return postfix;
}

long long zasulsky::solvePostfixExpr(Queue< std::string >& postfix)
{
  zasulsky::Stack < long long > st;
  while (!postfix.isEmpty())
  {
    std::string p = postfix.peek();
    if (isOperand(p))
    {
      try
      {
        auto np = stoll(p);
        st.push(np);
      }
      catch (const std::out_of_range& e)
      {
        throw std::runtime_error("overflow or underflow detected!");
      }
    }
    else
    {
      long long operand2 = st.top();
      st.pop();
      long long operand1 = st.top();
      st.pop();
      if (p == "^")
      {
        long long value = operand1;
        for (long long i = 1; i < operand2; i++)
        {
          if (value * operand1 > LLONG_MAX || value * operand1 < LLONG_MIN)
          {
            throw std::runtime_error("overflow or underflow detected!");
          }
          operand1 *= value;
        }
        st.push(operand1);
      }
      else if (p == "*")
      {
        if (LLONG_MAX / operand1 < operand2)
        {
          throw std::runtime_error("overflow or underflow detected!");
        }
        st.push(operand1 * operand2);
      }

      else if (p == "/")
      {
        if (operand2 == 0)
        {
          throw std::runtime_error("division by zero!");
        }
        st.push(operand1 / operand2);
      }

      else if (p == "%")
      {
        if (operand2 == 0)
        {
          throw std::runtime_error("division by zero!");
        }
        if ((operand1 % operand2) < 0)
        {
          st.push((operand1 % operand2) + operand2);
        }
        else
        {
          st.push(operand1 % operand2);
        }
      }

      else if (p == "+")
      {
        if (operand1 > 0 && operand2 > LLONG_MAX - operand1)
        {
          throw std::runtime_error("overflow or underflow detected!");
        }
        if (operand1 < 0 && operand2 < LLONG_MIN - operand1)
        {
          throw std::runtime_error("overflow or underflow detected!");
        }
        st.push(operand1 + operand2);
      }

      else if (p == "-")
      {
        if (operand2 > 0 && operand1 < LLONG_MIN + operand2)
        {
          throw std::runtime_error("overflow or underflow detected!");
        }
        if (operand2 < 0 && operand1 > LLONG_MAX + operand2)
        {
          throw std::runtime_error("overflow or underflow detected!");
        }
        st.push(operand1 - operand2);
      }
    }
    if (!postfix.isEmpty())
    {
      postfix.dequeue();
    }
  }
  if (st.getSize() == 1)
  {
    return st.top();
  }
  else
  {
    throw std::logic_error("in your infix expression two operands stand side by side!");
  }
}

void zasulsky::outputResults(Stack< long long >& results)
{
  while (!results.isEmpty())
  {
    std::cout << results.top();
    results.pop();
    if (results.isEmpty())
    {
      std::cout << '\n';
    }
    else
    {
      std::cout << ' ';
    }
  }
}
