#ifndef UTILS_HPP
#define UTILS_HPP

#include "tree.hpp"

using bigTreeDeclaration = sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< int, std::string, int >, int >;
using smallTreeDeclaration = sobolevsky::AVLtree< int, std::string, int >;

namespace sobolevsky
{
  void inputFromFile(std::istream &in, bigTreeDeclaration &data);
  void errorInvalidCommand(std::ostream &out);
  void errorEmpty(std::ostream &out);
  void checkName(bigTreeDeclaration &data, smallTreeDeclaration &newTree, std::string newName);
}

#endif
