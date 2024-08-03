#ifndef PROCESS_HPP
#define PROCESS_CPP
#include <iosfwd>
#include <string>
#include "BinarySearchTree.hpp"
#include "TreeTraversal.hpp"

namespace kovshikov
{
  bool isDigit(std::string str);
  void outText(std::ostream& out, std::string string);

  void readData(std::istream& in, Tree< int, std::string >& tree);
  void createTree(Tree< int, std::string >& tree, std::string dictionary);

  void getAscending(Tree< int, std::string >& tree);
  void getDescending(Tree< int, std::string >& tree);
  void getBreadth(Tree< int, std::string >& tree);

  void outTraversal(TreeTraversal& result);
}

#endif
