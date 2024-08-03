#include "functions.hpp"
#include <limits>
#include <cmath>
#include <iostream>
#include <commands.hpp>

std::string nikiforov::cutElements(std::string& str)
{
  std::string elem = str.substr(0, str.find_first_of(" ", 0));
  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return elem;
}

void nikiforov::convertToPostfix(std::string str, Queue< Initialization >& queue)
{
  Stack< Initialization > stack;
  std::string elem;

  while (!str.empty())
  {
    elem = cutElem(str);
    Initialization elemSeq(elem);

    if (elemSeq.type == operand)
    {
      queue.push_back(elemSeq);
    }
    else if (elemSeq.type == openBracket)
    {
      stack.push_back(elemSeq);
    }
    else if (elemSeq.type == closeBracket)
    {
      while (stack.back().type != openBracket)
      {
        queue.push_back(stack.back());
        stack.pop_back();
      }
      stack.pop_back();
    }
    else if (!stack.is_empty())
    {
      if (nikiforov::calculationPriority(elemSeq) <= nikiforov::calculationPriority(stack.back()))
      {
        queue.push_back(stack.back());
        stack.pop_back();
        stack.push_back(elemSeq);
      }
      else
      {
        stack.push_back(elemSeq);
      }
    }
    else
    {
      stack.push_back(elemSeq);
    }
  }
  while (!stack.is_empty())
  {
    if (stack.back().type == openBracket || stack.back().type == closeBracket)
    {
      throw std::logic_error("Error: wrong expression");
    }
    queue.push_back(stack.back());
    stack.pop_back();
  }
}

void nikiforov::calculation(Queue< Initialization >& Postfix, nikiforov::Stack< long long >& Result)
{
  nikiforov::Stack< long long > stack;
  Initialization elemSeq;
  while (!Postfix.is_empty())
  {
    elemSeq = Postfix.front();
    if (elemSeq.type == operand)
    {
      stack.push_back(elemSeq.operand_.data);
    }
    else
    {
      operations(elemSeq, stack);
    }
    Postfix.pop_front();
  }
  if (!stack.is_empty())
  {
    Result.push_back(stack.back());
  }
}

void nikiforov::operations(Initialization elemSeq, nikiforov::Stack< long long >& stack)
{
  long long rNum = stack.back();
  stack.pop_back();
  long long lNum = stack.back();
  stack.pop_back();

  long long minValue = std::numeric_limits< long long >::min();
  long long maxValue = std::numeric_limits< long long >::max();

  if (elemSeq.operation_.data == '+')
  {
    if (rNum > 0 && lNum > 0 && (rNum > maxValue - lNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    else if (rNum < 0 && lNum < 0 && (rNum < minValue - lNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    else
    {
      stack.push_back(lNum + rNum);
    }
  }
  else if (elemSeq.operation_.data == '-')
  {
    if (lNum > 0 && rNum < 0 && (lNum > maxValue + rNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    else if (lNum < 0 && rNum > 0 && (lNum < minValue + rNum))
    {
      throw std::overflow_error("Error: overflow");
    }
    else
    {
      stack.push_back(lNum - rNum);
    }
  }
  else if (elemSeq.operation_.data == '*')
  {
    if (((lNum > 0 && rNum > 0) || (lNum < 0 && rNum < 0)) && (abs(rNum) > abs(maxValue / lNum)))
    {
      throw std::overflow_error("Error: overflow");
    }
    else if (((lNum > 0 && rNum < 0) || (lNum < 0 && rNum > 0)) && (abs(rNum) > abs(minValue / lNum)))
    {
      throw std::overflow_error("Error: overflow");
    }
    else
    {
      stack.push_back(lNum * rNum);
    }
  }
  else if (elemSeq.operation_.data == '/')
  {
    stack.push_back(lNum / rNum);
  }
  else if (elemSeq.operation_.data == '%')
  {
    stack.push_back(((lNum % rNum + rNum) % rNum));
  }
  else
  {
    throw std::invalid_argument("Error: invalid operand");
  }
}

size_t nikiforov::calculationPriority(Initialization elemSeq)
{
  if (elemSeq.operation_.data == '+' || elemSeq.operation_.data == '-')
  {
    return 1;
  }
  else if (elemSeq.operation_.data == '*' || elemSeq.operation_.data == '/' || elemSeq.operation_.data == '%')
  {
    return 2;
  }
  else
  {
    return 0;
  }
}
