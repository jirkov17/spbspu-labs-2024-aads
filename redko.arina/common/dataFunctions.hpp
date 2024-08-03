#ifndef DATAFUNCTIONS_HPP
#define DATAFUNCTIONS_HPP
#include <string>
#include "binarySearchTree.hpp"

namespace redko
{
  int cutKey(std::string & str);
  void print(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr);
  void complement(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr);
  void intersect(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr);
  void unite(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr);
  void printMessage(std::ostream & out, const std::string & message);
}

#endif
