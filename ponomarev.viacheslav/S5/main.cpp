#include <iostream>
#include <fstream>
#include <functional>
#include "commands.hpp"
#include "IOFunctions.hpp"

using tree_t = ponomarev::BSTree< long long, std::string, long long >;

int main(int argc, char ** argv)
{
  if (argc != 3)
  {
    std::cerr << "wrong argc\n";
    return 2;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "can't open the file\n";
    return 2;
  }

  tree_t data;
  ponomarev::makeInput(input, data);

  if (data.isEmpty())
  {
    ponomarev::printEmptyDataset(std::cout);
    return 0;
  }

  ponomarev::BSTree< std::string, std::function< void(std::ostream &, tree_t &) >, long long > commands;
  {
    commands["ascending"] = ponomarev::makeAscending;
    commands["descending"] = ponomarev::makeDescending;
    commands["breadth"] = ponomarev::makeBreadth;
  }
  std::string direction = argv[1];

  try
  {
    commands.at(direction)(std::cout, data);
  }
  catch(const std::out_of_range &)
  {
    ponomarev::printInvalidCommandMessage(std::cout);
    data.clear();
    commands.clear();
    return 1;
  }
  data.clear();
  commands.clear();
  return 0;
}
