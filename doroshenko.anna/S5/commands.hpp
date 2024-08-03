#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "BinarySearchTree.hpp"

namespace doroshenko
{
  void strToTree(std::string expression, BST< int, std::string >& result);
  void ascending(std::ostream& out, const BST< int, std::string >& tree);
  void descending(std::ostream& out, const BST< int, std::string >& tree);
  void breadth(std::ostream& out, const BST< int, std::string >& tree);
  void outEmpty(std::ostream& out);
  void outInvCom(std::ostream& out);
  void outRange(std::ostream& out);
}

#endif
