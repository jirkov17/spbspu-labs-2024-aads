#include <iostream>
#include <fstream>
#include <string>
#include "commands.hpp"
#include "BinarySearchTree.hpp"

int main(int argc, char* argv[])
{
  using namespace doroshenko;
  BST< int, std::string > tree;
  if (argc != 3)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Wrong file\n";
    return 1;
  }
  std::string inputLine;
  std::getline(input, inputLine);
  try
  {
    strToTree(inputLine, tree);
  }
  catch (std::out_of_range& e)
  {
    outRange(std::cerr);
    return 1;
  }
  BST< std::string, std::function< void(std::ostream& out, BST< int, std::string >& tree) > > treeOfFuncs;
  treeOfFuncs.insert("ascending", ascending);
  treeOfFuncs.insert("descending", descending);
  treeOfFuncs.insert("breadth", breadth);
  std::string traverse = argv[1];
  if (treeOfFuncs.find(traverse) != treeOfFuncs.cend())
  {
    if (tree.getSize() == 0)
    {
      outEmpty(std::cout);
      return 0;
    }
    try
    {
      treeOfFuncs.at(traverse).second(std::cout, tree);
    }
    catch (const std::exception& e)
    {
      outInvCom(std::cerr);
      return 1;
    }
  }
  else
  {
    outInvCom(std::cerr);
    return 1;
  }
  return 0;
}
