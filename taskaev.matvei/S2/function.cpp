#include <string>
#include <limits>
#include "function.hpp"
#include "Queue.hpp"
#include "Stack.hpp"
#include "IdentifierMath.hpp"

namespace taskaev
{
  void inputMathValue(Queue< IdentifierMath >& queue, std::string mathValue)
  {
    std::string item;
    size_t i = 0;
    while( i < mathValue.length()) {
      if (mathValue[i] != ' ') {
        item += mathValue[i];
      }
      else {
        queue.push((IdentifierMath(item)));
        item = "";
      }
      i++;
    }
    queue.push(IdentifierMath(item));
  }

  void convertToPostfix(Queue< IdentifierMath >& queue, Queue< IdentifierMath >& postfix, Stack< IdentifierMath >& stack)
  {
    while (!queue.isEmpty()) {
      if (queue.front().types == operand)
      {
        postfix.push(queue.front());
        queue.pop();
      }
      else if (queue.front().types == operation)
      {
        if (!stack.isEmpty() && stack.top().types == operation)
        {
          int priorityStack = 0;
          int priorityQueue = 0;
          priorityStack = (stack.top().types == '+' || stack.top().types == '-') ? 1 : 2;
          priorityQueue = (queue.front().types == '+' || queue.front().types == '-') ? 1 : 2;
          if (priorityStack >= priorityQueue)
          {
            postfix.push(stack.top());
            stack.pop();
          }
        }
        stack.push(queue.front());
        queue.pop();
      }
      else if (queue.front().types == openParantheses)
      {
        stack.push(queue.front());
        queue.pop();
      }
      else if (queue.front().types == closedParantheses)
      {
        if (stack.isEmpty())
        {
          throw std::logic_error("Error: a lot of ) in prog SOS");
        }
        while (stack.top().types != openParantheses) {
          postfix.push(stack.top());
          stack.pop();
          if (stack.isEmpty())
          {
            std::logic_error("Error: please check the breckets");
          }
        }
        stack.pop();
        queue.pop();
      }
    }
    while (!stack.isEmpty())
    {
      if(stack.top().types == openParantheses)
      {
        throw std::logic_error( "Error: don't match expression ");
      }
      postfix.push(stack.top());
      stack.pop();
    }
  }

  long long calculate(Queue< IdentifierMath >& postfix)
  {
    Stack< long long > result;
    const long long maxLimit = std::numeric_limits< long long >::max();
    const long long minLimit = std::numeric_limits< long long >::min();
    while (!postfix.isEmpty())
    {
      if (postfix.front().types == operand)
      {
        result.push(postfix.front().operands.data);
      }
      else {
        long long operand = result.top();
        result.pop();
        if (postfix.front().operations.data == '+')
        {
          if(result.top() > maxLimit - operand)
          {
            throw std::logic_error("Error: overflow plus");
          }
          else
          {
            operand += result.top();
          }
        }
        else if (postfix.front().operations.data == '-')
        {
          if(result.top() < minLimit + operand)
          {
            throw std::logic_error("Erorr: overflow minus");
          }
          else
          {
            operand = result.top() - operand;
          }
        }
        else if (postfix.front().operations.data == '*')
        {
          if (operand > maxLimit / result.top() || operand < minLimit / result.top())
          {
            throw std::logic_error("Error: overflow multiplication");
          }
          else
          {
            operand *= result.top();
          }
        }
        else if (postfix.front().operations.data == '/')
        {
          if (operand != 0)
          {
            operand = result.top() / operand;
          }
          else
          {
            throw std::invalid_argument("Error: division by 0");
          }
        }
        else
        {
          if (operand != 0)
          {
            operand = (result.top() % operand < 0 ) ? ((result.top() % operand)+ operand) : (result.top() % operand);
          }
          else
          {
            throw std::invalid_argument("Error: division by 0");
          }
        }
        result.pop();
        result.push(operand);
      }
      postfix.pop();
    }
    if(result.isEmpty())
    {
      throw std::logic_error("Error: the problem in stack and valgrind");
    }
    {
      return result.top();
    }
  }
}
