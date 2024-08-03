#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "stack.hpp"
#include "queue.hpp"
#include "functions.hpp"

int main(int argc, char * argv[])
{
  using namespace khoroshkin;
  Stack< std::string > expressions;
  if (argc == 1)
  {
    inputInfix(std::cin, expressions);
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    inputInfix(input, expressions);
  }
  else
  {
    std::cerr << "Error: wrong input!";
    return 1;
  }
  while (!expressions.isEmpty())
  {
    try
    {
      std::cout << calculateExpression(expressions.top());
      expressions.pop();
      if (!expressions.isEmpty())
      {
        std::cout << ' ';
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }
  std::cout << '\n';
  return 0;
}
