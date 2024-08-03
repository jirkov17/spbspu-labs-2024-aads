#ifndef EXEC_COMMANDS_HPP
#define EXEC_COMMANDS_HPP
#include <iostream>
#include <string>
#include "avlTree.hpp"

namespace psarev
{
  using base_t = psarev::avlTree< int, std::string >;

  std::ostream& outInvCommand(std::ostream& out);
  std::ostream& outEmpty(std::ostream& out);

  void fillTree(std::istream& in, avlTree< std::string, base_t >& dataSets);

  void print(avlTree< std::string, avlTree< int, std::string > >& dataSets);
  void complement(avlTree< std::string, avlTree< int, std::string > >& dataSets);
  void intersect(avlTree< std::string, avlTree< int, std::string > >& dataSets);
  void unio(avlTree< std::string, avlTree< int, std::string > >& dataSets);
}

#endif
