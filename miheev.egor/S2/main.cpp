#include <iostream>
#include <fstream>
#include <istream>
#include "queue.hpp"
#include "expressionElement.hpp"
#include "inputProcessing.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;
  Stack< long long> results;
  try
  {
    if (argc == 2)
    {
      std::ifstream in(argv[1]);
      if (!in)
      {
        std::cerr << "error while opening the file or file is empty\n";
        return 1;
      }
      results = processInput(in);
    }
    else if (argc == 1)
    {
      results = processInput(std::cin);
    }
    if (!results.empty())
    {
      results.print(std::cout, ' ');
    }
    else
    {
      std::cout << '\n';
    }
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
