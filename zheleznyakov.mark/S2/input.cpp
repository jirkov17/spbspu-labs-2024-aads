#include "input.hpp"

void zheleznyakov::readLines(std::istream & input, Stack< std::string > & stack)
{
  std::string current;
  while (!input.eof())
  {
    std::getline(input, current);
    if (current != "")
    {
      stack.push(current);
    }
  }
}

void zheleznyakov::tokenize(std::string str, Queue< std::string > & dest)
{
  std::string currentToken;
  for (char c : str)
  {
    if (std::isspace(c))
    {
      if (!currentToken.empty())
      {
        dest.push(currentToken);
        currentToken.clear();
      }
    }
    else
    {
      currentToken += c;
    }
  }
  if (!currentToken.empty())
  {
    dest.push(currentToken);
  }
}

bool zheleznyakov::isOperator(const std::string & token)
{
  return token == "+" || token == "-" || token == "*" || token == "/" || token == "%";
}

int zheleznyakov::priority(const std::string & op)
{
  if (op == "*" || op == "/" || op == "%")
  {
    return 2;
  }
  else if (op == "+" || op == "-")
  {
    return 1;
  }
  return 0;
}

void zheleznyakov::infixToPostfix(Queue<std::string> & from, Queue<std::string> & to)
{
  Stack<std::string> operators;
  while (!from.empty())
  {
    std::string token = from.front();
    from.pop();

    if (token == "(")
    {
      operators.push(token);
    }
    else if (token == ")")
    {
      while (!operators.empty() && operators.top() != "(")
      {
        to.push(operators.top());
        operators.pop();
      }
      operators.pop();
    }
    else if (isOperator(token))
    {
      while (!operators.empty() && priority(operators.top()) >= priority(token))
      {
        to.push(operators.top());
        operators.pop();
      }
      operators.push(token);
    }
    else
    {
      to.push(token);
    }
  }
  while (!operators.empty())
  {
    to.push(operators.top());
    operators.pop();
  }
}
