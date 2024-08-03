#include "types.hpp"
#include <limits>
#include <cmath>
#include "list.hpp"
#include "processing.hpp"

mihalchenko::Operand::Operand(long long data)
{
  data_ = data;
}

mihalchenko::Operand mihalchenko::Operand::operator+(const Operand &rhs)
{
  Operand result;
  long long llMax = std::numeric_limits< long long >::max();
  if ((llMax - data_) < rhs.data_)
  {
    throw std::logic_error("Error: overflow!");
    std::cerr << "Overflow!\n";
    return result;
  }
  result.data_ = data_ + rhs.data_;
  return result;
}

mihalchenko::Operand mihalchenko::Operand::operator-(const Operand &rhs)
{
  Operand result;
  result.data_ = data_ - rhs.data_;
  return result;
}

mihalchenko::Operand mihalchenko::Operand::operator*(const Operand &rhs)
{
  Operand result;
  long long llMax = std::numeric_limits<long long>::max();
  if (llMax / data_ < rhs.data_)
  {
    throw std::logic_error("Error: overflow!");
    std::cerr << "Overflow!\n";
    return result;
  }
  result.data_ = data_ * rhs.data_;
  return result;
}

mihalchenko::Operand mihalchenko::Operand::operator/(const Operand &rhs)
{
  Operand result;
  if (rhs.data_ == 0)
  {
    throw std::logic_error("Error: division by zero!");
    std::cerr << "Division by zero!\n";
    return result;
  }
  result.data_ = data_ / rhs.data_;
  return result;
}

mihalchenko::Operand mihalchenko::Operand::operator%(const Operand &rhs)
{
  Operand result;
  if (data_ < 0)
  {
    result.data_ = abs((data_ / rhs.data_ - 1) * rhs.data_ - data_);
  }
  else
    result.data_ = data_ % rhs.data_;

  return result;
}

char mihalchenko::Operation::getOperation() const
{
  return command_;
}

void mihalchenko::Operation::setOperation(const char command)
{
  command_ = command;
  weightOfCommand_ = 0;
}

bool mihalchenko::FinalTransform::calculate()
{
  mihalchenko::List< char > list = mihalchenko::getListFromString("()+-*/%");
  char codOperation;
  Operand wremSave;
  Operand firstVal;
  Operand secondVal;

  if (calcRezult.getSize() == 1)
  {
    return true;
  }
  else if ((calcRezult.getSize() == 0) && (commands.getSize() == 1))
  {
    return true;
  }

  const size_t restrictionOfFormation = 4;
  while (commands.getSize() > 0)
  {
    size_t stepCounter = 0;
    codOperation = '.';
    bool flag = false;
    while (!flag)
    {
      for (size_t i = 0; i < list.getSize(); i++)
      {
        if (list[i] == codOperation)
        {
          flag = true;
        }
      }
      if (!flag)
      {
        codOperation = commands.getT();
        commands.pop();
        stepCounter++;
      }
    }
    if (stepCounter == restrictionOfFormation)
    {
      wremSave = calcRezult.getT();
      calcRezult.pop();
    }

    if (calcRezult.getSize() < 2)
    {
      std::cerr << "Data error!\n";
      return false;
    }
    else
    {
      firstVal = calcRezult.getT();
      calcRezult.pop();
      secondVal = calcRezult.getT();
      calcRezult.pop();
    }
    if (codOperation == '+')
    {
      calcRezult.push(firstVal + secondVal);
    }
    if (codOperation == '-')
    {
      calcRezult.push(firstVal - secondVal);
    }
    if (codOperation == '*')
    {
      calcRezult.push(firstVal * secondVal);
    }
    if (codOperation == '/')
    {
      calcRezult.push(firstVal / secondVal);
    }
    if (codOperation == '%')
    {
      calcRezult.push(firstVal % secondVal);
    }
    if (codOperation == '(' || codOperation == ')')
    {
      calcRezult.push(codOperation);
    }
    if (commands.getSize() != 0)
    {
      commands.push('.');
    }
    if (stepCounter == restrictionOfFormation)
    {
      calcRezult.push(wremSave);
      commands.push('.');
    }
  }
  return true;
}
