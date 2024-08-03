#ifndef OUTPUTFUNCTIONS_HPP
#define OUTPUTFUNCTIONS_HPP
#include <string>
#include <ostream>
#include "list.hpp"

namespace redko
{
  std::ostream & printElementsInOrder(std::ostream & out, const List< std::pair< std::string, List< unsigned long long > > > & list);
  List< unsigned long long > * calculateSums(List< std::pair< std::string, List< unsigned long long > > > & list);
}

#endif
