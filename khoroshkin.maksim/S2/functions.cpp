#include "functions.hpp"
#include "typization.hpp"

void khoroshkin::inputInfix(std::istream & in, Stack< std::string > & expressions)
{
  std::string expression;
  while (getline(in, expression))
  {
    if (expression.length() > 0)
    {
      expressions.push("( " + expression + " )");
    }
  }
}

bool khoroshkin::isDigit(const std::string & str)
{
  for (char c : str)
  {
    if (!std::isdigit(c))
    {
      return false;
    }
  }
  return !str.empty();
}

long long khoroshkin::calculateExpression(const std::string & str)
{
  Postfix expression;
  size_t pos = 0;
  std::string token;
  do
  {
    token = getToken(str, pos);
    if (khoroshkin::isDigit(token))
    {
      try
      {
        expression.operands.push(std::stoll(token));
      }
      catch (const std::out_of_range & e)
      {
        throw e;
      }
    }
    else if (token.size() == 1)
    {
      Bracket bracket(token[0]);
      if (bracket.isBracket() && !bracket.isBracketOpen())
      {
        bracket = expression.operations.top().operation;
        while (!expression.operations.isEmpty() && !bracket.isBracketOpen())
        {
          expression.popOperation();
          bracket = expression.operations.top().operation;
        }
        expression.operations.pop();
      }
      else
      {
        while (expression.canPop(token[0]))
        {
          expression.popOperation();
        }
        expression.operations.push((token[0]));
      }
    }
  }
  while (!token.empty());

  if (expression.operands.getSize() > 1 || !expression.operations.isEmpty())
  {
    throw std::logic_error("Error: wrong expression");
  }
  long long result = expression.operands.top().value;
  expression.operands.pop();
  return result;
}

std::string khoroshkin::getToken(const std::string & str, size_t & pos)
{
  skipWhitespace(str, pos);
  if (pos == str.length())
  {
    return "";
  }
  else if (std::isdigit(str[pos]))
  {
    return readOperand(str, pos);
  }
  else
  {
    return std::string(1, readOperation(str, pos));
  }
}

std::string khoroshkin::readOperand(const std::string & str, size_t & pos)
{
  std::string result = "";
  while (pos < str.length() && std::isdigit(str[pos]))
  {
    result += str[pos++];
  }
  return result;
}

char khoroshkin::readOperation(const std::string & str, size_t & pos)
{
  return str[pos++];
}

void khoroshkin::skipWhitespace(const std::string & str, size_t & pos)
{
  if (pos < str.length() && str[pos] == ' ')
  {
    pos++;
  }
}
