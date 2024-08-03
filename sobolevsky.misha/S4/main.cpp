#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <functional>
#include <limits>
#include "tree.hpp"
#include "commands.hpp"
#include "utils.hpp"

using treeDeclaration = sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< int, std::string, int >, int >;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "missed filename\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "file cannot be opened\n";
    return 1;
  }

  treeDeclaration tree;
  sobolevsky::inputFromFile(file, tree);
  sobolevsky::AVLtree< std::string, std::function< void(std::istream &, std::ostream &, treeDeclaration &) >, int > cmds;
  cmds["print"] = sobolevsky::getPrint;
  cmds["complement"] = std::bind(sobolevsky::getComplement, std::placeholders::_1, std::placeholders::_3);
  cmds["intersect"] = std::bind(sobolevsky::getIntersect, std::placeholders::_1, std::placeholders::_3);
  cmds["union"] = std::bind(sobolevsky::getUnion, std::placeholders::_1, std::placeholders::_3);
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout, tree);
    }
    catch(const std::out_of_range & e)
    {
      sobolevsky::errorInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  for (treeDeclaration::Iterator iter = tree.begin(); iter != tree.end(); iter++)
  {
    iter->second.clear();
  }
  tree.clear();
  cmds.clear();

  return 0;
}
