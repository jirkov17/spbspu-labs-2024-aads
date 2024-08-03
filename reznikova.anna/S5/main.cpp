#include <functional>
#include <iostream>
#include <fstream>
#include <Tree.hpp>
#include "Commands.hpp"
#include "TreeProcessing.hpp"

int main(int argc, char ** argv)
{
  using namespace reznikova;
  if (argc != 3)
  {
    std::cerr << "wrong number of args\n";
    return 1;
  }
  Tree< int, std::string > tree;
  std::fstream input(argv[2]);
  if (!input)
  {
    std::cerr << "can't read from file\n";
    return 1;
  }
  Tree< std::string, std::function< void(Tree< int, std::string > &) > > commands;
  commands.insert("ascending", ascendingCommand);
  commands.insert("descending", descendingCommand);
  commands.insert("breadth", breadthCommand);
  try
  {
    readFromFile(input, tree);
    commands.at(argv[1])(tree);
  }
  catch(const std::exception& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  return 0;
}
