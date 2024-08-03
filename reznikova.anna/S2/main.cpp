#include <iostream>
#include <fstream>
#include "InputProcessing.hpp"

int main(int argc, char ** argv)
{
  reznikova::Queue< reznikova::Element > infix;
  reznikova::Postfix postfix;
  long long int calculate_result = 0;
  reznikova::Stack< long long int > results;
  try
  {
    if (argc == 2)
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "can't open file\n";
        return 1;
      }
      else
      {
        while (!input.eof())
        {
          reznikova::readLine(input, infix);
          reznikova::makePostfix(infix, postfix);
          if (!postfix.postfix_.empty())
          {
            calculate_result = reznikova::calculate(postfix);
            results.push(calculate_result);
          }
        }
      }
    }
    else if (argc == 1)
    {
      while (!std::cin.eof())
      {
        reznikova::readLine(std::cin, infix);
        reznikova::makePostfix(infix, postfix);
        if (!postfix.postfix_.empty())
        {
          calculate_result = reznikova::calculate(postfix);
          results.push(calculate_result);
        }
      }
    }
    else
    {
      std::cerr << "too much arguments\n";
      return 1;
    }
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what();
    return 1;
  }
  while (!results.empty())
  {
    std::cout << results.getValue();
    if (results.getSize() != 1)
    {
      std::cout << " ";
    }
    results.pop();
  }
  std::cout << "\n";
  return 0;
}
