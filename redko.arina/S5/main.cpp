#include <iostream>
#include <fstream>
#include <functional>
#include <inputFunctions.hpp>
#include <dataFunctions.hpp>
#include "binarySearchTree.hpp"
#include "sumAndOrder.hpp"

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  redko::BSTree< std::string, std::function< redko::SumAndOrder(redko::BSTree< int, std::string > *, redko::SumAndOrder) > > functions{};
  functions.insert({ "ascending", &redko::BSTree< int, std::string >::traverseLR< redko::SumAndOrder > });
  functions.insert({ "descending", &redko::BSTree< int, std::string >::traverseRL< redko::SumAndOrder > });
  functions.insert({ "breadth", &redko::BSTree< int, std::string >::traverseBreadth< redko::SumAndOrder > });

  redko::BSTree< int, std::string > data{};
  std::string description = "";
  std::getline(input, description);
  std::string elem = "";
  int key = 0;
  while (!description.empty())
  {
    try
    {
      key = redko::cutKey(description);
    }
    catch (const std::out_of_range &)
    {
      std::cerr << "Error: out of range value\n";
      return 1;
    }
    elem = redko::cutName(description);
    data.insert({ key, elem });
  }
  if (!data.empty())
  {
    if (functions.find(argv[1]) != functions.end())
    {
      redko::SumAndOrder result{};
      try
      {
        result = functions[argv[1]](&data, redko::SumAndOrder());
      }
      catch (const std::out_of_range & e)
      {
        std::cerr << e.what() << '\n';
        return 1;
      }
      std::cout << result.sum;
      while (!result.valueOrder.empty())
      {
        std::cout << ' ' << result.valueOrder.front();
        result.valueOrder.pop();
      }
      std::cout << '\n';
    }
    else
    {
      std::cerr << "Error: invalid parameter\n";
      return 2;
    }
  }
  else
  {
    redko::printMessage(std::cout, "<EMPTY>");
  }
  return 0;
}
