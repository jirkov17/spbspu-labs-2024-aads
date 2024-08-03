#ifndef TRAVERSE_CMDS_HPP
#define TRAVERSE_CMDS_HPP
#include <iostream>
#include <string>
#include <avlTree.hpp>

namespace psarev
{
  std::ostream& outInvCommand(std::ostream& out);
  std::ostream& outEmpty(std::ostream& out);

  using base_t = psarev::avlTree< long long, std::string >;

  void fillTree(std::istream& in, base_t& data);

  void ascending(std::ostream& out, base_t& data);
  void descending(std::ostream& out, base_t& data);
  void breadth(std::ostream& out, base_t& data);
}

#endif
