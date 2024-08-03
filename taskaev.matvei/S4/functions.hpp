#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include "BSTree.hpp"
#include <iostream>
#include <fstream>
#include <string>

namespace taskaev
{
  using Tree = BSTree< std::string, BSTree< size_t, std::string > >;
  using SubTree = BSTree< size_t, std::string >;

  void createTree(std::istream& in, Tree& tree);

  void print(Tree& tree);

  void complement(Tree& tree);
  void findComplement(SubTree& two, SubTree& one, SubTree& tres);

  void intersect(Tree& tree);

  void unions(Tree& tree);
  SubTree mergeTrees(SubTree& treeOne, SubTree& treeTwo);

  void errorInvalid(std::ostream& out);
  void errorEmpty(std::ostream& out);
}

#endif
