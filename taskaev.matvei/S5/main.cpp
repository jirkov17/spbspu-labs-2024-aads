#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "functions.hpp"
#include <BSTree.hpp>

int main(int argc, char ** argv)
{
  using namespace taskaev;
  if (argc != 3)
  {
    std::cerr << "Error: arguments invalid!\n";
    return 1;
  }
  BSTree< int, std::string> tree;
  std::fstream inputs(argv[2]);
  if (!inputs)
  {
    std::cerr << "Error: not open file!\n";
    return 1;
  }
  std::string name = argv[1];
  try
  {
    createTree(inputs, tree);
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  BSTree< std::string, std::function< void(BSTree< int, std::string >&) > > cmds;
  cmds.insert("ascending", ascending);
  cmds.insert("descending", descending);
  cmds.insert("breadth", breadth);
  try
  {
    cmds.at(name)(tree);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what();
    return 1;
  }
  return 0;
}
