#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "binarySearchTreeAVL.hpp"
#include "IOFunctions.hpp"

using data_t = ponomarev::BSTree< int, std::string, int >;
using tree_t = ponomarev::BSTree< std::string, data_t, int >;

namespace ponomarev
{
  void makePrint(std::istream & in, std::ostream & out, tree_t & data);
  void makeComplement(std::istream & in, std::ostream &, tree_t & data);
  void makeIntersect(std::istream & in, std::ostream &, tree_t & data);
  void makeUnion(std::istream & in, std::ostream &, tree_t & data);
}

#endif
