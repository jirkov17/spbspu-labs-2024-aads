#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include "Tree.hpp"
#include "Commands.hpp"

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "wrong number of args\n";
    return 1;
  }
  using namespace reznikova;
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Can't read from file\n";
    return 2;
  }
  Tree< std::string, Tree< size_t, std::string > > treeMap;
  readFromFile(input, treeMap);

  Tree< std::string, std::function < void(Tree< std::string, Tree< size_t, std::string > >&) > > commands;
  commands.insert("print", printCommand);
  commands.insert("complement", complementCommand);
  commands.insert("intersect", intersectCommand);
  commands.insert("union", unionCommand);
  std::string command;
  while(std::cin >> command)
  {
    try
    {
      commands.at(command)(treeMap);
    }
    catch(const std::out_of_range& error)
    {
      outputInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
