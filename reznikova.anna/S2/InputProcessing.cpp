#include "InputProcessing.hpp"
#include <cstddef>
#include <limits>
#include <cmath>
#include <iostream>

void reznikova::readLine(std::istream & is, reznikova::Queue< reznikova::Element > & infix)
{
  std::string input;
  std::getline(is, input);
  std::string data;
  for (size_t i = 0; i < input.length(); i++)
  {
    if (input[i] == ' ' or i == (input.length()-1))
    {
      if (i == (input.length()-1))
      {
        data += input[i];
      }
      if (data == "(")
      {
        Element input_bracket;
        input_bracket.types_ = open_bracket_type;
        input_bracket.elem_.open_bracket_ = Bracket{ data[0] };
        infix.push(input_bracket);
      }
      else if (data == ")")
      {
        Element input_bracket;
        input_bracket.types_ = close_bracket_type;
        input_bracket.elem_.close_bracket_ = Bracket{ data[0] };
        infix.push(input_bracket);
      }
      else if (data == "+" or data == "-" or data == "*" or data == "/" or data == "%")
      {
        Element input_operator;
        input_operator.types_ = operator_type;
        input_operator.elem_.operator_ = Operator{ data[0] };
        infix.push(input_operator);
      }
      else
      {
        Element input_operand;
        input_operand.types_ = operand_type;
        input_operand.elem_.operand_ = Operand{ data };
        infix.push(input_operand);
      }
      data = "";
    }
    else
    {
      data += input[i];
    }
  }
}

bool reznikova::ifFirstPriority(reznikova::Element & element)
{
  return (element.elem_.operator_.operator_ == '+' or element.elem_.operator_.operator_ == '-');
}

bool reznikova::ifEquallyImportant(reznikova::Stack< reznikova::Element > & stack, reznikova::Element & element)
{
  while(!stack.empty())
  {
    if (ifFirstPriority(element))
    {
      return ifFirstPriority(stack.getValue()) ? true : false;
    }
    else
    {
      return true;
    }
  }
  return false;
}

void reznikova::makePostfix(reznikova::Queue< reznikova::Element > & infix, reznikova::Postfix & postfix)
{
  Stack< Element > stack;
  while (!infix.empty())
  {
    Element element = infix.getValue();
    if (element.types_ == open_bracket_type)
    {
      stack.push(element);
    }
    else if (element.types_ == close_bracket_type)
    {
      while (stack.getValue().types_ == operator_type)
      {
        postfix.postfix_.push(stack.getValue());
        stack.pop();
      }
      stack.pop();
    }
    else if (element.types_ == operand_type)
    {
      postfix.postfix_.push(element);
    }
    else if (element.types_ == operator_type)
    {
      while (!stack.empty() and stack.getValue().types_ == operator_type and ifEquallyImportant(stack, element))
      {
        postfix.postfix_.push(stack.getValue());
        stack.pop();
      }
      stack.push(element);
    }
    infix.pop();
  }
  while (!stack.empty())
  {
    if (stack.getValue().types_ == open_bracket_type)
    {
      throw std::logic_error("wrong expression\n");
    }
    postfix.postfix_.push(stack.getValue());
    stack.pop();
  }
}

long long int reznikova::calculate(reznikova::Postfix & postfix)
{
  const long long int maximum = std::numeric_limits< long long int >::max();
  Stack< Element > stack;
  while(!postfix.postfix_.empty())
  {
    Element element = postfix.postfix_.getValue();
    if (element.getType() == type_t::operand_type)
    {
      stack.push(element);
    }
    else
    {
      Operand first_operand = stack.getValue().getOperand();
      stack.pop();
      Operand second_operand = stack.getValue().getOperand();
      stack.pop();
      Operand result_operand;
      if (element.elem_.operator_.operator_ == '+')
      {
        if (maximum - second_operand.operand_ < first_operand.operand_)
        {
          throw std::overflow_error("too big numbers\n");
        }
        result_operand = first_operand + second_operand;
      }
      else if (element.getOperator().operator_ == '-')
      {
        result_operand = second_operand - first_operand;
      }
      else if (element.getOperator().operator_ == '/')
      {
        result_operand = second_operand / first_operand;
      }
      else if (element.getOperator().operator_ == '%')
      {
        if (second_operand.operand_ < 0)
        {
          result_operand.operand_ = second_operand.operand_ - (first_operand.operand_ * floor(second_operand.operand_/first_operand.operand_ - 1));
        }
        else
        {
          result_operand = second_operand % first_operand;
        }
      }
      else if (element.getOperator().operator_ == '*')
      {
        if (maximum / second_operand.operand_ < first_operand.operand_)
        {
          throw std::overflow_error("too big numbers\n");
        }
        result_operand = first_operand * second_operand;
      }
      Element el;
      el.types_ = operator_type;
      el.elem_.operand_ = result_operand;
      stack.push(el);
    }
    postfix.postfix_.pop();
  }
  return stack.getValue().getOperand().operand_;
}
