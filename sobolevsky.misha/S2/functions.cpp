#include "functions.hpp"
#include <sstream>
#include <limits>

void sobolevsky::fillStack(std::istream & in, Stack< std::string > & container)
{
  std::string input;
  while (getline(in, input))
  {
    if(input.length() == 0)
    {
      continue;
    }
    container.push(input);
  }
}

bool sobolevsky::isDigit(std::string c)
{
  for(unsigned long i = 0; i < c.length(); i++)
  {
    if (!('0' <= c[i] && c[i] <= '9'))
    {
      return false;
    }
  }
  return true;
}

int sobolevsky::algebrChars(std::string c)
{
  if (c == "/" || c == "*" || c == "%")
  {
    return 2;
  }
  else if (c == "+" || c == "-")
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

long long sobolevsky::counter(std::string ch, long long first, long long second)
{
  long long limitMax = std::numeric_limits< long long >::max();
  long long limitMin = std::numeric_limits< long long >::min();
  if(ch == "+")
  {
    if ((limitMax - first) < second || (limitMax - second) < first)
    {
      throw std::logic_error("overflow");
    }
    return first + second;
  }
  else if(ch == "-")
  {
    if ((limitMin + second) > first || (limitMin + first) > second)
    {
      throw std::logic_error("overflow");
    }
    return first - second;
  }
  else if(ch == "*")
  {
    if ((limitMax / second) < first || ((limitMin / second) > first))
    {
      throw std::logic_error("overflow");
    }
    return first * second;
  }
  else if(ch == "/")
  {
    if ((limitMin / second) > first)
    {
      throw std::logic_error("overflow");
    }
    return first / second;
  }
  else
  {
    if (first < 0)
    {
      return second + (first % second);
    }
    else
    {
      return first % second;
    }
  }
}

std::shared_ptr< std::string[] > sobolevsky::fromInfixToPostfix(std::string infixExpression, long long &i)
{
  std::shared_ptr< std::string[] > postfixExpression(new std::string[infixExpression.length()]());
  std::string str;
  Stack< std::string > stack;
  std::stringstream ss(infixExpression);
  while (getline(ss, str, ' '))
  {
    if (isDigit(str))
    {
      postfixExpression[i] = str;
      i++;
    }
    else if (str == "(")
    {
      stack.push("(");
    }
    else if (str == ")")
    {
      while (stack.top() != "(")
      {
        postfixExpression[i] = stack.top();
        i++;
        stack.pop();
      }
      stack.pop();
    }
    else
    {
      while (!stack.empty() && algebrChars(str) <= algebrChars(stack.top()))
      {
        postfixExpression[i] = stack.top();
        i++;
        stack.pop();
      }
      stack.push(str);
    }
  }

  while (!stack.empty())
  {
    postfixExpression[i] = stack.top();
    i++;
    stack.pop();
  }

  return postfixExpression;
}

long long sobolevsky::countPostfix(std::shared_ptr< std::string[] > postfix, long long length)
{
  Stack< long long > stack;

  for (long long j = 0; j < length; j++)
  {
    if (isDigit(postfix[j]))
    {
      stack.push(std::stoll(postfix[j]));
    }
    else
    {
      long long second = stack.top();
      stack.pop();
      long long first = stack.top();
      stack.pop();
      long long result = counter(postfix[j], first, second);
      stack.push(result);
    }
  }

  return stack.top();
}
