#ifndef TREEPROCESS_HPP
#define TREEPROCESS_HPP
#include <string>
#include "BinarySearchTree.hpp"

namespace kovshikov
{
  void readData(std::istream& in, Tree< std::string, Tree< size_t, std::string > >& allTree);
  void createTree(Tree< std::string, Tree< size_t, std::string > >& allTree, std::string dictionary);
  bool isDigit(std::string str);

  void print(Tree< std::string, Tree< size_t, std::string > >& allTree);
  void getComplement(Tree< std::string, Tree< size_t, std::string > >& allTree);
  void getIntersect(Tree< std::string, Tree< size_t, std::string > >& allTree);
  void getUnion(Tree< std::string, Tree< size_t, std::string > >& allTree);

  void outText(std::ostream& out, std::string string);
}

#endif
