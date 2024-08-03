#ifndef TREETRAVERSAL_HPP
#define TREETRAVERSAL_HPP

#include <BinarySearchTree.hpp>
#include "KeySum.hpp"

namespace zhitnyj {
  void traverseAscending(const BSTree< long long, std::string > &tree);
  void traverseDescending(const BSTree< long long, std::string > &tree);
  void traverseBreadth(const BSTree< long long, std::string > &tree);
  void printResult(KeySum &keySumCounter, std::ostream &os);
  void invalidCommandError(std::ostream &out);
  void emptyCommandWarning(std::ostream &out);
}

#endif
