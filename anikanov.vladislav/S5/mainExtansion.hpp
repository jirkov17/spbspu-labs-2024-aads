#ifndef MAINEXTANSION_HPP
#define MAINEXTANSION_HPP

#include <iosfwd>
#include <string>
#include <binarySearchTree.hpp>

namespace anikanov {
  bool loadTreeFromFile(std::string &fileName, BinarySearchTree< long long, std::string, std::less<> > &tree);
  void printInvalidUsage(std::ostream &os, char *argv[]);
  void printInvalidMode(std::ostream &os);
  void printEmpty(std::ostream &os);
  void printError(std::ostream &os, const std::string &error);
}

#endif
