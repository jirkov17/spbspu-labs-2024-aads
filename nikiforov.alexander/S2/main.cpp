#include <iostream>
#include <fstream>
#include "functions.hpp"

int main(int argc, char* argv[])
{
  using namespace nikiforov;

  Stack< long long > Result;
  Queue< Initialization > Postfix;
  std::string infix = "";

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

      while (!input.eof())
      {
        std::getline(input, infix);
        convertToPostfix(infix, Postfix);
        calculation(Postfix, Result);
      }
    }
    else if (argc == 1)
    {
      while (!std::cin.eof())
      {
        std::getline(std::cin, infix);
        convertToPostfix(infix, Postfix);
        calculation(Postfix, Result);
      }
    }
    else
    {
      std::cerr << "Error: wrong number of parameters\n";
    }

    while (!Result.is_empty())
    {
      std::cout << Result.back();
      if (Result.getSize() == 1)
      {
        Result.pop_back();
      }
      else
      {
        std::cout << " ";
        Result.pop_back();
      }
    }
    std::cout << "\n";

  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
