#ifndef TREEPROCESSING_HPP
#define TREEPROCESSING_HPP
#include <iosfwd>
#include <Tree.hpp>
#include "TraverseObject.hpp"

namespace reznikova
{
  void outputInvalidCommand(std::ostream & out);
  void outputEmptyError(std::ostream & out);
  std::string getValue(std::string & input, size_t & i);
  int getKey(std::string & input, size_t & i);
  void readFromFile(std::istream & is, Tree< int, std::string > & tree);
  void output(Traverse & functor);
}

#endif
