#include <iostream>
#include <iosfwd>
#include <string>
#include <fstream>
#include "DataProcessing.hpp"
#include "DataTypes.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

int main(int argc, char* argv[])
{
  using namespace sukacheva;
  Stack< long long > resultsOfCalculate;
  if (argc == 1)
  {
    try
    {
      while (!std::cin.eof())
      {
        Queue< std::string > inf = inputStatement(std::cin);
        Postfix statement = makePostfix(inf);
        if (!statement.postfix.empty())
        {
          resultsOfCalculate.push(calculate(statement));
        }
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else if (argc == 2)
  {
    try
    {
      std::ifstream input(argv[1]);
      if (!input)
      {
        std::cerr << "unable to open file !!" << "\n";
        return 1;
      }
      else
      {
        while (!input.eof())
        {
          Queue< std::string > inf = inputStatement(input);
          Postfix statement = makePostfix(inf);
          if (!statement.postfix.empty())
          {
            resultsOfCalculate.push(calculate(statement));
          }
        }
      }
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  else
  {
    std::cerr << "wrong number of args";
  }
  while (!resultsOfCalculate.empty())
  {
    std::cout << resultsOfCalculate.top();
    resultsOfCalculate.pop();
    if (!resultsOfCalculate.empty())
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";
  return 0;
}
