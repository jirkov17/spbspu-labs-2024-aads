#include <iostream>
#include <fstream>
#include <functional>
#include <tree.hpp>
#include "commands.hpp"
#include "errorsANDinput.hpp"

using treeDeclaration = sobolevsky::AVLtree< long long, std::string, long long >;

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    std::cerr << "missed some argc\n";
    return 1;
  }
  std::string detourDirection = argv[1];
  std::ifstream file(argv[2]);
  if (!file)
  {
    std::cerr << "file cannot be opened\n";
    return 1;
  }
  treeDeclaration tree;
  sobolevsky::inputFromFile(file, tree);
  if (tree.isEmpty())
  {
    sobolevsky::errorEmpty(std::cout);
    return 0;
  }
  sobolevsky::AVLtree< std::string, std::function< void(std::ostream &, const treeDeclaration &) >, long long > cmds;
  cmds["ascending"] = sobolevsky::ascending;
  cmds["descending"] = sobolevsky::descending;
  cmds["breadth"] = sobolevsky::breadth;
  try
  {
    cmds.at(detourDirection)(std::cout, tree);
  }
  catch(const std::exception & e)
  {
    sobolevsky::errorOverflowOrOutOfRange(std::cerr);
    tree.clear();
    cmds.clear();
    return 1;
  }
  tree.clear();
  cmds.clear();
  return 0;
}
