#include <iostream>
#include <fstream>
#include "processingFunctions.hpp"

int main(int argc, char ** argv)
{
  redko::Stack< long long > results{};
  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "Error: unable to open the file\n";
        return 2;
      }
      processExpressions(input, results);
    }
    else
    {
      processExpressions(std::cin, results);
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  while (!results.empty())
  {
    std::cout << results.top();
    results.pop();
    if (!results.empty())
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
  return 0;
}
