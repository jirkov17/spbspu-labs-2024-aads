#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include "BST.hpp"

namespace sukacheva
{
  using treeOfTrees = BST< std::string, BST< size_t, std::string > >;

  void printCommand(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out);
  void print(treeOfTrees& treeOfDicts, std::string name, std::ostream& out);
  void comlement(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out);
  void intersect(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out);
  void unionCommand(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out);

  void inputTree(treeOfTrees& treeOfDicts, std::string& line);
}

#endif
