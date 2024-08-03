#include <iostream>
#include <fstream>
#include "inputFunctions.hpp"

int main(int argc, char ** argv)
{
  ponomarev::Queue< std::string > expressions;
  ponomarev::Stack< long long > results;

  if (argc == 1)
  {
    ponomarev::inputExpressions(std::cin, expressions);
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    ponomarev::inputExpressions(input, expressions);
  }
  else
  {
    std::cerr << "Error: wrong input";
    return 1;
  }

  try
  {
    ponomarev::getResults(expressions, results);
  }
  catch (const std::exception & e)
  {
    std::cout << e.what();
    return 1;
  }

  while (!results.isEmpty())
  {
    std::cout << results.getUp();
    results.pop();
    if (!results.isEmpty())
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';

  return 0;
}
