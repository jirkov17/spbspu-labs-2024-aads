#include "calculationProcess.hpp"
#include <limits>

void doroshenko::readInfixForm(std::istream& input, Queue< std::string >& result)
{
  std::string inputLine;
  while (!input.eof())
  {
    std::getline(input, inputLine);
    if (!inputLine.empty())
    {
      result.push(inputLine);
    }
  }
}

void doroshenko::strToQueue(std::string expression, Queue< std::string >& result)
{
  std::string symbol = "";
  size_t i = 0;
  while (i < expression.length())
  {
    if (expression[i] == ' ')
    {
      i++;
      result.push(symbol);
      symbol = "";
    }
    else if (i == (expression.length() - 1))
    {
      symbol += expression[i];
      i++;
      result.push(symbol);
    }
    else
    {
      symbol += expression[i];
      i++;
    }
  }
}

bool doroshenko::isOperand(std::string symbol)
{
  for (char c : symbol)
  {
    if (!std::isdigit(c))
    {
      return false;
    }
  }
  return true;
}

bool doroshenko::isOperator(std::string c)
{
  if (c == "/" || c == "*" || c == "+" || c == "-" || c == "%")
  {
    return true;
  }
  return false;
}

int doroshenko::precendence(std::string c)
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

void doroshenko::infixToPostfix(Queue< std::string >& expression, Queue< std::string >& result)
{
  Stack< std::string > stack;

  while (!expression.isEmpty())
  {
    std::string elem = expression.front();
    expression.drop();
    if (isOperand(elem))
    {
      result.push(elem);
    }
    else if (elem == "(")
    {
      stack.push("(");
    }
    else if (elem == ")")
    {
      while (stack.front() != "(")
      {
        result.push(stack.front());
        stack.drop();
      }
      stack.drop();
    }
    else
    {
      while ((!stack.isEmpty() && precendence(elem) < precendence(stack.front())) ||
      (!stack.isEmpty() && precendence(elem) == precendence(stack.front())))
      {
        result.push(stack.front());
        stack.drop();
      }
      stack.push(elem);
    }
  }
  while (!stack.isEmpty())
  {
    result.push(stack.front());
    stack.drop();
  }
}

long long doroshenko::countOperation(long long fval, long long sval, std::string operation)
{
  long long result = 0;
  long long maximum = std::numeric_limits< long long >::max();
  long long minimum = std::numeric_limits< long long >::min();
  if (operation == "+")
  {
    if (maximum - fval < sval)
    {
      throw std::overflow_error("overflow error");
    }
    else
    {
      result = fval + sval;
      return result;
    }
  }
  else if (operation == "-")
  {
    if (fval < minimum + sval)
    {
      throw std::underflow_error("underflow error");
    }
    else
    {
      result = fval - sval;
      return result;
    }
  }
  else if (operation == "*")
  {
    if (maximum / fval < sval)
    {
      throw std::overflow_error("overflow error");
    }
    else
    {
      result = fval * sval;
      return result;
    }
  }
  else if (operation == "/")
  {
    result = fval / sval;
    return result;
  }
  else if (operation == "%")
  {
    if (fval < 0)
    {
      result = fval % sval + sval;
      return result;
    }
    else
    {
      result = fval % sval;
      return result;
    }
  }
  else
  {
    return 0;
  }
}

long long doroshenko::calculateExpr(Queue< std::string >& expression)
{
  Stack< long long > stack;
  std::string elem;
  long long fval;
  long long sval;
  while (!expression.isEmpty())
  {
    elem = expression.front();
    expression.drop();
    if (isOperand(elem))
    {
      stack.push(std::stoll(elem));
    }
    else if (isOperator(elem))
    {
      sval = stack.front();
      stack.drop();
      fval = stack.front();
      stack.drop();
      stack.push(countOperation(fval, sval, elem));
    }
    else
    {
      throw std::logic_error("incorrect expression");
    }
  }
  unsigned long long result = stack.front();
  stack.drop();
  return result;
}

void doroshenko::formResultStack(Queue< std::string >& expressions, Stack< long long >& resultStack)
{
  std::string curStrExpr;
  Queue< std::string > curInfixExpr;
  Queue< std::string > curPostfixExpr;
  long long curAnswer = 0;
  while (!expressions.isEmpty())
  {
    curStrExpr = expressions.front();
    expressions.drop();
    strToQueue(curStrExpr, curInfixExpr);
    infixToPostfix(curInfixExpr, curPostfixExpr);
    curAnswer = calculateExpr(curPostfixExpr);
    resultStack.push(curAnswer);
  }
}

