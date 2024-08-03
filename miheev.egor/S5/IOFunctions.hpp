#ifndef IO_FUNCTIONS_HPP
#define IO_FUNCTIONS_HPP

#include <ios>
#include <tree.hpp>

namespace miheev
{
  using tree_t = Tree< long long, std::string >;
  void readTree(std::istream&, tree_t&);
  void sendEmpty(std::ostream&);
}

#endif
