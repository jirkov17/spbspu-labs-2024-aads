#include <fstream>
#include "calculationProcess.hpp"

int main(int argc, char* argv[])
{
  using namespace doroshenko;
  Queue< std::string > expressions;
  Stack< long long > resultStack;

  if (argc == 1)
  {
    readInfixForm(std::cin, expressions);
  }
  else if (argc == 2)
  {
    std::ifstream input(argv[1]);
    readInfixForm(input, expressions);
  }
  else
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  try
  {
    formResultStack(expressions, resultStack);
    while (!resultStack.isEmpty())
    {
      std::cout << resultStack.front();
      if (resultStack.front() != resultStack.back())
      {
        std::cout << ' ';
      }
      resultStack.drop();
    }
    std::cout << '\n';
  }
  catch (const std::exception &e)
  {
    std::cout << e.what();
    return 1;
  }
  return 0;
}
