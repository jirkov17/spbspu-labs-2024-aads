#include "processingFunctions.hpp"
#include "inputFunctions.hpp"
#include "postfix.hpp"

bool redko::isNumeric(const std::string & str)
{
  return str.find_first_not_of("0123456789") == std::string::npos && str.size() != 0;
}

redko::ExprElem redko::cutElem(std::string & str)
{
  redko::ExprElem res;
  std::string value = cutName(str);
  if (isNumeric(value))
  {
    res.elem.operand = Operand(stoll(value));
    res.type = operand;
  }
  else if (value == "(" || value == ")")
  {
    res.type = bracket;
    res.elem.bracket = Bracket{ value[0] };
  }
  else if (value == "+" || value == "-" || value == "%" || value == "*" || value == "/")
  {
    res.type = operation;
    res.elem.operation = Operation{ value[0] };
  }
  else
  {
    throw std::invalid_argument("Error: wrong expression");
  }
  return res;
}

void redko::processExpressions(std::istream & input, Stack< long long > & res)
{
  std::string expression = "";
  while (!input.eof())
  {
    Postfix postfix{};
    Stack< ExprElem > stack{};
    std::getline(input, expression);
    while (!expression.empty())
    {
      ExprElem elem = cutElem(expression);
      if (elem.type == operand)
      {
        postfix.postfix.push(elem);
      }
      else if (elem.type == bracket)
      {
        if (elem.elem.bracket.bracket == '(')
        {
          stack.push(elem);
        }
        else
        {
          while (!stack.empty() && stack.top().type != bracket)
          {
            postfix.postfix.push(stack.top());
            stack.pop();
          }
          stack.pop();
        }
      }
      else if (elem.type == operation)
      {
        while (!stack.empty() && stack.top().type == operation && elem.elem.operation <= stack.top().elem.operation)
        {
          postfix.postfix.push(stack.top());
          stack.pop();
        }
        stack.push(elem);
      }
    }
    while (!stack.empty())
    {
      postfix.postfix.push(stack.top());
      stack.pop();
    }
    if (!postfix.postfix.empty())
    {
      res.push(postfix.calculate());
    }
  }
}
