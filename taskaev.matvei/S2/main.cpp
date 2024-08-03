#include <iostream>
#include <fstream>
#include <string>
#include "Queue.hpp"
#include "Stack.hpp"
#include "function.hpp"
#include "IdentifierMath.hpp"

int main(int argc, char * argv[])
{
  using namespace taskaev;
  Queue< IdentifierMath > queue;
  Queue< IdentifierMath > postfix;
  Stack< IdentifierMath > stack;
  Stack< long long > results;
  std::string mathValue;
  if (argc == 1)
  {
    while (!std::cin.eof())
    {
      std::getline(std::cin, mathValue);
      if (!mathValue.empty())
      {
        try
        {
          inputMathValue(queue, mathValue);
          convertToPostfix(queue, postfix, stack);
          results.push(calculate(postfix));
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << "\n";
          return 1;
        }
      }
    }
  }
  else if (argc == 2)
  {
    std::ifstream input;
    input.open(argv[1]);
    if (!input.is_open())
    {
      std::cerr << " Error: file not open! ";
      return 1;
    }
    while (std::getline(input, mathValue))
    {
      if (!mathValue.empty())
      {
        try
        {
          inputMathValue(queue, mathValue);
          convertToPostfix(queue, postfix, stack);
          results.push(calculate(postfix));
        }
        catch (const std::exception& e)
        {
          std::cerr << e.what() << "\n";
          return 1;
        }
      }
    }
    input.close();
  }
  else
  {
    std::cerr << "Erro: arguments, don't be greedy add more!\n";
    return 1;
  }
  while (!results.isEmpty())
  {
    std::cout << results.top();
    results.pop();
    if (!results.isEmpty())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}

