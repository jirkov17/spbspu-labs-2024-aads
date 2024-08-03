#include <iostream>
#include <fstream>
#include <limits>
#include <cctype>
#include "processing.hpp"

int main(int argc, char *argv[])
{
  using namespace mihalchenko;
  Queue< std::string > resiveDigit;
  Stack< std::string > resiveControl;
  Stack< long long > calculateResult;
  std::string currentStr;
  resiveControl.setSize(0);
  calculateResult.setSize(0);
  resiveDigit.setSize(0);
  if (argc == 1)
  {
    while (std::getline(std::cin, currentStr, '\n'))
    {
      try
      {
        if (!bildStrPostFix(currentStr, currentStr.size(), resiveDigit, resiveControl))
        {
          std::cerr << "Error: wrong input!\n";
          return 1;
        }
        calculateResult.setSize(calculatePostFix(resiveDigit, calculateResult));
        size_t llMax = std::numeric_limits< long long >::max();
        if (calculateResult.getSize() == llMax)
        {
          return 1;
        }
      }
      catch (...)
      {
        std::cerr << "Exception!\n";
        return 5;
      }
    }
  }
  else if (argc == 2)
  {
    std::ifstream inputFF;
    inputFF.open(argv[1]);
    while (std::getline(inputFF, currentStr, '\n'))
    {
      try
      {
        if (!bildStrPostFix(currentStr, currentStr.size(), resiveDigit, resiveControl))
        {
          std::cerr << "Error: wrong input!\n";
          return 1;
        }
        calculateResult.setSize(calculatePostFix(resiveDigit, calculateResult));
        size_t llMax = std::numeric_limits< long long >::max();
        if (calculateResult.getSize() == llMax)
        {
          return 1;
        }
      }
      catch (...)
      {
        std::cerr << "Exception!\n";
        return 3;
      }
    }
    inputFF.close();
  }
  else
  {
    std::cerr << "Error: wrong input!";
    return 1;
  }

  size_t num = calculateResult.getSize();
  printedResult(std::cout, calculateResult, num);
  return 0;
}
