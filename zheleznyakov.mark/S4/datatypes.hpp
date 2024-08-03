#ifndef DATATYPES_HPP
#define DATATYPES_HPP
#include <tree.hpp>

namespace zheleznyakov
{
  using dict_t = Tree< int, std::string >;
  using dicts_t = Tree< std::string, dict_t >;
}
#endif
