#include <iostream>
#include <fstream>
#include <string>
#include <Queue.hpp>
#include <Stack.hpp>
#include "ExpressionItem.hpp"
#include "ExpressionEvaluator.hpp"

int main(int argc, char* argv[])
{
  zhitnyj::Queue< std::shared_ptr< zhitnyj::ExpressionItem > > expressionQueue;
  zhitnyj::Stack< long long > results;

  try
  {
    std::string line;
    if (argc > 1)
    {
      std::ifstream file(argv[1]);
      if (!file)
      {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 1;
      }
      while (std::getline(file, line))
      {
        if (!line.empty())
        {
          zhitnyj::ExpressionEvaluator::parseExpression(expressionQueue, line);
          zhitnyj::Queue< std::shared_ptr< zhitnyj::ExpressionItem > > postfixQueue = zhitnyj::ExpressionEvaluator::toPostfix(expressionQueue);
          results.push(zhitnyj::ExpressionEvaluator::evaluateExpression(postfixQueue));
          expressionQueue.clear();
        }
      }
    }
    else
    {
      while (std::getline(std::cin, line))
      {
        if (!line.empty())
        {
          zhitnyj::ExpressionEvaluator::parseExpression(expressionQueue, line);
          zhitnyj::Queue< std::shared_ptr< zhitnyj::ExpressionItem > > postfixQueue = zhitnyj::ExpressionEvaluator::toPostfix(expressionQueue);
          results.push(zhitnyj::ExpressionEvaluator::evaluateExpression(postfixQueue));
          expressionQueue.clear();
        }
      }
    }

    while (!results.empty())
    {
      std::cout << results.top() << (results.size() == 1 ? "" : " ");
      results.pop();
    }
    std::cout << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  return 0;
}
