#include "computationalFunctions.hpp"
#include "stack.hpp"
#include "cutFunctions.hpp"

void ponomarev::getPostfix(std::string expression, Postfix & queue)
{
  Stack< ExpressionElement > stack;

  while (!(expression.empty()))
  {
    ExpressionElement elem = getElem(expression);
    if (elem.getType() == "Bracket")
    {
      if (elem.getBracket().bracket_ == '(')
      {
        stack.push(elem);
      }
      else
      {
        while (!(isOpenBracketUp(stack)))
        {
          queue.postfix_.push(stack.getUp());
          stack.pop();
        }
        stack.pop();
      }
    }
    else if (elem.getType() == "Operand")
    {
      queue.postfix_.push(elem);
    }
    else if (elem.getType() == "Operation")
    {
      while (!shouldPushOpToStack(stack, elem))
      {
        queue.postfix_.push(stack.getUp());
        stack.pop();
      }
      stack.push(elem);
    }
  }
  while (!stack.isEmpty())
  {
    queue.postfix_.push(stack.getUp());
    stack.pop();
  }
}

bool ponomarev::isNum(const std::string & elem)
{
  return elem.find_first_not_of("0123456789") == std::string::npos && elem.size() != 0;
}

bool ponomarev::isOpenBracketUp(const Stack< ExpressionElement > & stack)
{
  if (stack.isEmpty())
  {
    return false;
  }

  bool isBracketUp = stack.getUp().getType() != "Bracket";
  if (isBracketUp)
  {
    return false;
  }

  bool bracketIsOpening = stack.getUp().getBracket().bracket_ != '(';
  if (bracketIsOpening)
  {
    return false;
  }

  return true;
}

bool ponomarev::shouldPushOpToStack(const Stack< ExpressionElement > & stack, const ExpressionElement & elem)
{
  if (stack.isEmpty())
  {
    return true;
  }

  bool isOperationUp = stack.getUp().getType() != "Operation";
  if (isOperationUp)
  {
    return true;
  }

  if (elem.getOperation().priority_ < stack.getUp().getOperation().priority_)
  {
    return true;
  }

  return false;
}

ponomarev::ExpressionElement ponomarev::getElem(std::string & expression)
{
  ponomarev::ExpressionElement elem;
  std::string arg = getName(expression);
  if (isNum(arg))
  {
    elem.putOperand(std::stoll(arg));
  }
  else if (arg == "+" || arg == "-" || arg == "%" || arg == "*" || arg == "/")
  {
    elem.putOperation(arg[0]);
  }
  else if (arg == "(" || arg == ")")
  {
    elem.putBracket(arg[0]);
  }
  else
  {
    throw std::invalid_argument("Error: wrong expression");
  }
  return elem;
}

long long ponomarev::calculate(std::string & expression)
{
  Postfix postfix;
  getPostfix(expression, postfix);
  Stack< Operand > stack;

  while (!postfix.postfix_.isEmpty())
  {
    ExpressionElement elem = postfix.postfix_.getElem();
    postfix.postfix_.pop();
    if (elem.getType() == "Operand")
    {
      stack.push(elem.getOperand());
    }
    else if (elem.getType() == "Operation")
    {
      Operand right = stack.getUp();
      stack.pop();
      Operand left = stack.getUp();
      stack.pop();
      Operand res = elem.getOperation().useOperation(left, right);
      stack.push(res);
    }
    else
    {
      throw std::logic_error("Unsupported expression element occured while calculating expr\n");
    }
  }

  return stack.getUp().getValue();
}
