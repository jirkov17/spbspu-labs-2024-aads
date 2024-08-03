#include <limits>
#include <stdexcept>
#include <memory>
#include <cmath>
#include <string>
#include <cctype>
#include "ExpressionEvaluator.hpp"

void zhitnyj::ExpressionEvaluator::parseExpression(zhitnyj::Queue< std::shared_ptr< zhitnyj::ExpressionItem > >& qe, const std::string& ep)
{
  std::string token;
  for (size_t i = 0; i < ep.length(); ++i)
  {
    char c = ep[i];
    if (std::isspace(c))
    {
      if (!token.empty())
      {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1])))
        {
          qe.push(std::make_shared< Operand >(std::stoll(token)));
        }
        else if (token.size() == 1 && Operator::isOperator(token[0]))
        {
          qe.push(std::make_shared< Operator >(token[0]));
        }
        else
        {
          throw std::runtime_error("Invalid token in ep: " + token);
        }
        token.clear();
      }
    }
    else
    {
      token += c;
    }
  }

  if (!token.empty())
  {
    if (std::isdigit(token[0]) || (token[0] == '-' && token.size() > 1 && std::isdigit(token[1])))
    {
      qe.push(std::make_shared< Operand >(std::stoll(token)));
    }
    else if (token.size() == 1 && Operator::isOperator(token[0]))
    {
      qe.push(std::make_shared< Operator >(token[0]));
    }
    else
    {
      throw std::runtime_error("Invalid token in expression: " + token);
    }
  }
}

zhitnyj::Queue< std::shared_ptr< zhitnyj::ExpressionItem > >
zhitnyj::ExpressionEvaluator::toPostfix(zhitnyj::Queue< std::shared_ptr< zhitnyj::ExpressionItem > >& inQe)
{
  Stack< std::shared_ptr< ExpressionItem > > operatorStack;
  Queue< std::shared_ptr< ExpressionItem > > postfixQueue;

  while (!inQe.empty())
  {
    std::shared_ptr< ExpressionItem > item = inQe.front();
    inQe.pop();

    if (item->isOperand())
    {
      postfixQueue.push(item);
    }
    else if (item->isOperator())
    {
      auto operator_ = std::dynamic_pointer_cast< Operator >(item);

      if (operator_->isLeftParenthesis())
      {
        operatorStack.push(operator_);
      }
      else if (operator_->isRightParenthesis())
      {
        while (!operatorStack.empty() && !std::dynamic_pointer_cast< Operator >(operatorStack.top())->isLeftParenthesis())
        {
          postfixQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.pop();
      }
      else
      {
        while (!operatorStack.empty()
            && std::dynamic_pointer_cast< Operator >(operatorStack.top())->precedence() >= operator_->precedence()
            && !std::dynamic_pointer_cast< Operator >(operatorStack.top())->isLeftParenthesis())
        {
          postfixQueue.push(operatorStack.top());
          operatorStack.pop();
        }
        operatorStack.push(operator_);
      }
    }
  }

  while (!operatorStack.empty())
  {
    postfixQueue.push(operatorStack.top());
    operatorStack.pop();
  }

  return postfixQueue;
}

long long zhitnyj::ExpressionEvaluator::evaluateExpression(zhitnyj::Queue< std::shared_ptr< zhitnyj::ExpressionItem > >& postfixQueue)
{
  Stack< long long > evaluationStack;

  while (!postfixQueue.empty())
  {
    std::shared_ptr< ExpressionItem > item = postfixQueue.front();
    postfixQueue.pop();

    if (item->isOperand())
    {
      auto operand = std::dynamic_pointer_cast< Operand >(item);

      evaluationStack.push(operand->getValue());
    }
    else if (item->isOperator())
    {
      auto op = std::dynamic_pointer_cast< Operator >(item);

      if (evaluationStack.size() < 2)
      {
        throw std::runtime_error("Insufficient values in the ep for operation");
      }
      long long right = evaluationStack.top();
      evaluationStack.pop();
      long long left = evaluationStack.top();
      evaluationStack.pop();
      bool add_overflow = op->getOperator() == '+' && (left > (std::numeric_limits< long long >::max() - right));
      bool multiply_overflow = op->getOperator() == '*' && (std::abs(left) > (std::numeric_limits< long long >::max() / right));
      bool minus_overflow = op->getOperator() == '-' && (left < (std::numeric_limits< long long >::min() + right));
      bool divide_overflow = op->getOperator() == '/' && ((left == std::numeric_limits< long long >::min()) && right == -1);

      if (add_overflow || multiply_overflow)
      {
        throw std::overflow_error("There was an overflow error!");
      }
      else if (minus_overflow || divide_overflow)
      {
        throw std::overflow_error("There was an underflow error!");
      }
      long long result = op->applyOp(left, right);
      evaluationStack.push(result);
    }
    else
    {
      throw std::runtime_error("Invalid expresssion item encountered");
    }
  }

  if (evaluationStack.size() != 1)
  {
    throw std::runtime_error("The expression does not reduce to a single value");
  }

  return evaluationStack.top();
}
