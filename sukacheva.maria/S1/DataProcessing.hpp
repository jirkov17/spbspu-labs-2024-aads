#ifndef DATAPROCESSING_HPP
#define DATAPROCESSING_HPP

#include <iosfwd>
#include "List.hpp"

namespace sukacheva {
  using listOfPairs = List< std::pair< std::string, List< size_t > > >;
  listOfPairs listInput(std::istream& in);
  size_t maxListSize(listOfPairs& newList);
  void printNameList(listOfPairs& newList);
  void printArgs(listOfPairs& newList, bool& overflowFlag, List< size_t >& sumOfArgs);
  void getSumsList(List< size_t >& sumOfArgs);
}

#endif
