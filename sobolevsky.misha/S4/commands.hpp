#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "tree.hpp"

using bigTreeDeclaration = sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< int, std::string, int >, int >;
using smallTreeDeclaration = sobolevsky::AVLtree< int, std::string, int >;

namespace sobolevsky
{
  void getPrint(std::istream &in, std::ostream &out, bigTreeDeclaration &data);
  void getComplement(std::istream &in, bigTreeDeclaration &data);
  void getIntersect(std::istream &in, bigTreeDeclaration &data);
  void getUnion(std::istream &in, bigTreeDeclaration &data);
}

#endif
