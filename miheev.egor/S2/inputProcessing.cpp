#include "inputProcessing.hpp"
#include "expressionElement.hpp"
#include "postfixElement.hpp"
#include "queue.hpp"

namespace miheev
{
  std::string getSymbol(std::string&);
  element_t convertToElement(std::string);
  element_t getElement(std::string&);
  Queue< postfix_t > lineToPosfix(std::string line);
  long long calcLine(std::string);
  void printTypes(miheev::Queue< element_t >);
}

std::string miheev::getSymbol(std::string& s)
{
  std::string symbol = s.substr(0, s.find(" "));
  if (s.find(" ") == std::string::npos)
  {
    s = "";
  }
  else
  {
    s = s.substr(s.find(" ") + 1);
  }
  return symbol;
}

miheev::element_t miheev::convertToElement(std::string s)
{
  miheev::element_t result;
  if (s == "+" || s == "-" || s == "*" || s == "/" || s == "%")
  {
    result.setOperation(s[0]);
  }
  else if (s == "(")
  {
    result.setParenthesis(s[0]);
  }
  else if (s == ")")
  {
    result.setParenthesis(')');
  }
  else
  {
    result.setOperand(stoll(s));
  }
  return result;
}

miheev::element_t miheev::getElement(std::string& s)
{
  std::string symbol = getSymbol(s);
  miheev::element_t element = miheev::convertToElement(symbol);
  return element;
}

bool isOpeningParenthesisOnTop(const miheev::Stack< miheev::element_t >& stack)
{
  if (stack.empty())
  {
    return false;
  }
  bool parenthesisOnTop = stack.top().getType() != "parenthesis";
  if (parenthesisOnTop)
  {
    return false;
  }
  bool parenthesisIsOpening = stack.top().getParenthesis().parenthesis != '(';
  if (parenthesisIsOpening)
  {
    return false;
  }
  return true;
}

bool shouldPushOpToStack(const miheev::Stack< miheev::element_t >& stack, const miheev::element_t& curr)
{
  if (stack.empty())
  {
    return true;
  }
  bool operationOnTop = stack.top().getType() != "operation";
  if (operationOnTop)
  {
    return true;
  }
  bool currOperationHasLessPriority = curr.getOperation() < stack.top().getOperation();
  if (currOperationHasLessPriority)
  {
    return true;
  }
  return false;
}

miheev::Queue< miheev::postfix_t > miheev::lineToPosfix(std::string line)
{
  Stack< miheev::element_t > stack;
  Queue< miheev::postfix_t > queue;
  miheev::element_t current;
  while (line != "")
  {
    current = getElement(line);
    if (current.getType() == "parenthesis")
    {
      if (current.getParenthesis().parenthesis == '(')
      {
        stack.push(current);
      }
      else
      {
        while (!isOpeningParenthesisOnTop(stack))
        {
          miheev::postfix_t temp(stack.top());
          stack.pop();
          queue.push(temp);
        }
        stack.pop();
      }
    }
    else if (current.getType() == "operand")
    {
      miheev::postfix_t temp(current);
      queue.push(temp);
    }
    else if (current.getType() == "operation")
    {
      while (!shouldPushOpToStack(stack, current))
      {
        miheev::postfix_t temp(stack.top());
        stack.pop();
        queue.emplace(temp);
      }
      stack.push(current);
    }
  }
  while (!stack.empty())
  {
    miheev::postfix_t temp(stack.top());
    queue.push(temp);
    stack.pop();
  }
  return queue;
}

void miheev::printTypes(miheev::Queue< miheev::element_t > q)
{
  while (!q.empty())
  {
    std::cout << q.front().getType() << ' ';
    q.pop();
  }
  std::cout << '\n';
}

long long miheev::calcLine(std::string line)
{
  miheev::Stack< Operand > stack;
  Queue< miheev::postfix_t > postfix = miheev::lineToPosfix(line);
  while (!postfix.empty())
  {
    miheev::postfix_t current = postfix.front();
    postfix.pop();
    if (current.getType() == "operand")
    {
      stack.push(current.getOperand());
    }
    else if(current.getType() == "operation")
    {
      Operand rhs = stack.top();
      stack.pop();
      Operand lhs = stack.top();
      stack.pop();
      stack.push(current.getOperation().implement(lhs, rhs));
    }
    else
    {
      throw std::logic_error("Unsupported expression element occured while calculating expr\n");
    }
  }
  if (stack.size() > 1)
  {
    throw std::runtime_error("not all operands are used. check your expression");
  }
  return stack.top().getValue();
}

miheev::Stack< long long > miheev::processInput(std::istream& in)
{
  Stack< long long > results;
  Queue< element_t > postfix;
  std::string line = "";
  while (!in.eof())
  {
    std::getline(in, line);
    if (line != "")
    {
      results.push(miheev::calcLine(line));
    }
  }
  return results;
}
