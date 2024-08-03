#ifndef PARSENUMS_HPP
#define PARSENUMS_HPP
#include <iostream>
#include "list.hpp"

namespace hohlova
{
  unsigned long long ParseNum(const std::string& str, size_t& pos);

  template< typename T >
  std::ostream& operator<<(std::ostream& os, const hohlova::List< T >& list);
}

#endif
