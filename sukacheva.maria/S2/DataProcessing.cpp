#include "DataProcessing.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Stack.hpp"
#include "Queue.hpp"

sukacheva::Queue< std::string > sukacheva::inputStatement(std::istream& input)
{
  input >> std::noskipws;
  std::string line = "";
  std::string num = "";
  Queue< std::string > statement;
  std::getline(input, line);
  for (size_t i = 0; i < line.length(); i++)
  {
    if (line[i] == ' ')
    {
      if (!num.empty())
      {
        statement.push(num);
      }
      num = "";
    }
    else
    {
      num += line[i];
    }
  }
  if (!num.empty())
  {
    statement.push(num);
  }
  return statement;
}

sukacheva::Postfix sukacheva::makePostfix(Queue< std::string >& infix)
{
  sukacheva::Stack< ElementOfStatement > temp;
  sukacheva::Postfix postfix;
  while (!infix.empty()) {
    ElementOfStatement val = infix.front();
    if (val.isBracket())
    {
      Bracket bracket = val.applicant;
      if (bracket.ifBracketIsOpen())
      {
        temp.push(Bracket('('));
        infix.pop();
      }
      else if (bracket.ifBracketIsClose())
      {
        if (temp.empty())
        {
          throw std::logic_error("incorrect statement notation :)");
        }
        else
        {
          while (!temp.top().isBracket())
          {
            postfix.postfix.push(temp.top());
            temp.pop();
          }
          infix.pop();
          temp.pop();
        }
      }
    }
    else if (val.isNumber())
    {
      postfix.postfix.push(Operand(std::stoll(val.applicant)));
      infix.pop();
    }
    else if (val.isBinaryOperations())
    {
      Operation operation = val.applicant;
      if (!temp.empty())
      {
        while (!temp.empty() && operation.priorityOfOperation(temp.top().applicant))
        {
          postfix.postfix.push(temp.top());
          temp.pop();
        }
      }
      temp.push(operation);
      infix.pop();
    }
    else
    {
      throw std::logic_error("invalid argument >:( ");
    }
  }
  while (!temp.empty())
  {
    if (!temp.top().isBracket())
    {
      postfix.postfix.push(temp.top());
      temp.pop();
    }
    else
    {
      throw std::logic_error("incorrect statement notation :)");
    }
  }
  return postfix;
}

long long sukacheva::calculate(Postfix& postfix)
{
  Stack< long long > stack;
  const long long maxValue = std::numeric_limits< long long >::max();
  const long long minValue = std::numeric_limits< long long >::min();
  while (!postfix.postfix.empty())
  {
    if (postfix.postfix.front().isNumber())
    {
      stack.push(std::stoll(postfix.postfix.front().applicant));
      postfix.postfix.pop();
    }
    else if (postfix.postfix.front().isBinaryOperations())
    {
      if (stack.getSize() >= 2)
      {
        long long operand2 = stack.top();
        stack.pop();
        long long operand1 = stack.top();
        stack.pop();

        if (postfix.postfix.front().applicant == "+")
        {
          if (operand1 > maxValue - operand2)
          {
            throw std::logic_error("overflow observed !!!");
          }
          else
          {
            stack.push(operand1 + operand2);
          }
        }
        else if (postfix.postfix.front().applicant == "-")
        {
          if (operand1 < minValue + operand2)
          {
            throw std::logic_error("overflow observed !!!");
          }
          else
          {
            stack.push(operand1 - operand2);
          }
        }
        else if (postfix.postfix.front().applicant == "*")
        {
          if ((operand1 >= maxValue / operand2) || (operand1 <= minValue / operand2))
          {
            throw std::logic_error("overflow observed !!!");
          }
          else
          {
            stack.push(operand1 * operand2);
          }
        }
        else if (postfix.postfix.front().applicant == "/")
        {
          if ((operand1 / operand2 >= maxValue) || (operand1 / operand2 <= minValue))
          {
            throw std::logic_error("overflow observed !!!");
          }
          else if (operand2 != 0)
          {
            stack.push(operand1 / operand2);
          }
          else
          {
            throw std::logic_error("division by zero !!!");
          }
        }
        else if (postfix.postfix.front().applicant == "%")
        {
          stack.push((operand1 % operand2) < 0 ? (operand1 % operand2) + operand2 : (operand1 % operand2));
        }
        postfix.postfix.pop();
      }
      else
      {
        throw std::logic_error("incorrect statement notation :)");
      }
    }
  }
  return stack.top();
}
