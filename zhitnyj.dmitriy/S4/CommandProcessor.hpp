#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include <string>
#include <map>
#include <functional>
#include "BinarySearchTree.hpp"

namespace zhitnyj {
  void processLineToTree(const std::string &line, BSTree< std::string, BSTree< long long, std::string > > &dict);
  void loadTreeFromFile(const std::string &file_, BSTree< std::string, BSTree< long long, std::string > > &dict);
  void handlePrint(BSTree< std::string, BSTree< long long, std::string > > &dict);
  void handleComplement(BSTree< std::string, BSTree< long long, std::string > > &dict);
  void handleIntersect(BSTree< std::string, BSTree< long long, std::string > > &dict);
  void handleUnion(BSTree< std::string, BSTree< long long, std::string > > &dict);
  void invalidCommandWarning(std::ostream &out);
  void emptyCommandWarning(std::ostream &out);
}

#endif
