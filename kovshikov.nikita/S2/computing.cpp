#include <cstring>
#include "computing.hpp"

void kovshikov::readData(std::istream& in, Queue< std::string >& allData)
{
  while(!in.eof())
  {
    std::string expression = "";
    std::getline(in, expression);
    if(!expression.empty())
    {
      allData.push(expression);
    }
  }
}

void kovshikov::separateElements(std::string str, Queue< std::string >& queue)
{
  std::string temp = "";
  size_t sizeStr = str.length();
  for(size_t i = 0; i < sizeStr; i++)
  {
    if(str[i] != ' ')
    {
      temp += str[i];
    }
    else
    {
      queue.push(temp);
      temp = "";
    }
  }
  queue.push(temp);
}

void kovshikov::separateElements(Queue< std::string > oldQ, doubleQ& sepQ)
{
  size_t size = oldQ.getSize();
  for(size_t i = 0; i < size; i++)
  {
    Queue< std::string > queue;
    separateElements(oldQ.front(), queue);
    oldQ.pop();
    sepQ.push(queue);
  }
}

int kovshikov::getPriority(char c)
{
  if (c == '/' || c == '*' || c == '%')
  {
    return 2;
  }
  else if( c == '+' || c == '-')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

bool kovshikov::isDigit(std::string str)
{
  size_t size = str.length();
  for(size_t i = 0; i < size; i++)
  {
    if(!std::isdigit(str[i]))
    {
      return false;
    }
  }
  return true;
}

void kovshikov::getPostfix(Queue< std::string >& oldQ, Queue< std::string >& newQ)
{
  bool isCorrect = true;
  Stack< std::string > stack;
  std::string element = "";
  size_t size = oldQ.getSize();
  for(size_t i = 0; i < size; i++)
  {
    element = oldQ.front();
    oldQ.pop();
    if(isDigit(element))
    {
      newQ.push(element);
    }
    else if(element[0] == '(')
    {
      isCorrect = false;
      stack.push(element);
    }
    else if(element[0] == ')')
    {
      isCorrect = true;
      while(stack.top()[0] != '(')
      {
        newQ.push(stack.top());
        stack.pop();
      }
      stack.pop();
    }
    else
    {
      while(!stack.isEmpty() && getPriority(element[0]) <= getPriority(stack.top()[0]))
      {
        newQ.push(stack.top());
        stack.pop();
      }
      stack.push(element);
    }
  }
  while(!stack.isEmpty())
  {
    newQ.push(stack.top());
    stack.pop();
  }
  if(isCorrect == false)
  {
    throw std::domain_error("A single opening bracket");
  }
}

void kovshikov::getPostfix(doubleQ oldQ, doubleQ& newQ)
{
  size_t size = oldQ.getSize();
  for(size_t i = 0; i < size; i++)
  {
    Queue< std::string > queue;
    try
    {
      getPostfix(oldQ.front(), queue);
    }
    catch(const std::exception &error)
    {
      throw;
    }
    oldQ.pop();
    newQ.push(queue);
  }
}

long long kovshikov::getComputation(Queue< std::string > queue)
{
  long long min = std::numeric_limits< long long >::min();
  long long max = std::numeric_limits< long long >::max();
  Stack< long long > stack;
  size_t size = queue.getSize();
  for(size_t i = 0; i < size; i++)
  {
    std::string element = queue.front();
    queue.pop();
    if(isDigit(element))
    {
      long long integer = std::stoll(element);
      if(integer == min)
      {
        throw std::underflow_error("You've gone out of range long long от -9223372036854775808");
      }
      stack.push(integer);
    }
    else
    {
      long long upperOperand = stack.top();
      stack.pop();
      long long operand = stack.top();
      stack.pop();
      if(element == "+")
      {
        long long summa = operand + upperOperand;
        if(operand > 0 && upperOperand > 0 && summa < 0 )
        {
          throw std::overflow_error("overflow after summa");
        }
        stack.push(summa);
      }
      else if(element == "-")
      {
        stack.push(operand - upperOperand);
      }
      else if(element == "*")
      {
        bool condOperand = operand > max / std::abs(upperOperand) || operand < min / std::abs(upperOperand);
        bool condUOperand = upperOperand > max / std::abs(operand) || upperOperand < min / std::abs(operand);
        if(condOperand || condUOperand)
        {
          throw std::range_error("range violation during multiplication");
        }
        stack.push(operand * upperOperand);
      }
      else if(element == "/")
      {
        stack.push(operand / upperOperand);
      }
      else if(element == "%")
      {
        if(operand > 0)
        {
          stack.push(operand % upperOperand);
        }
        else
        {
          long long part = std::abs(operand / upperOperand);
          part++;
          long long temp = part * upperOperand;
          stack.push(operand + temp);
        }
      }
    }
  }
  return stack.top();
}

void kovshikov::getComputation(doubleQ data, Stack< long long >& result)
{
  long long outcome;
  size_t size = data.getSize();
  for(size_t i = 0; i < size; i++)
  {
    Queue< std::string > temp = data.front();
    data.pop();
    try
    {
      outcome = getComputation(temp);
    }
    catch(const std::exception &error)
    {
      throw;
    }
    result.push(outcome);
  }
}

void kovshikov::output(std::ostream& out, Stack< long long > result)
{
  size_t size = result.getSize();
  for(size_t i = 0; i < size; i++)
  {
    if(i == size - 1)
    {
      out << result.top();
      result.pop();
    }
    else
    out << result.top() << " ";
    result.pop();
  }
  out << "\n";
}
