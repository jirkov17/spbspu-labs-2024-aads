#ifndef DETAILS_HPP
#define DETAILS_HPP
#include <map>
#include <string>
#include <iostream>
#include <AVLtree.hpp>

namespace mihalchenko
{
  using dictElement_t = std::pair< std::string, size_t >;
  using dict_t = AVLTree< std::string, size_t >;
  using mapOfDicts_t = AVLTree< std::string, dict_t >;
}

#endif
