#ifndef IOPROCESS_HPP
#define IOPROCESS_HPP
#include <iosfwd>
#include <string>
#include "doublelist.hpp"

namespace kovshikov
{
  using listPair = DoubleList< std::pair< std::string, DoubleList< size_t > > >;
  using listOfList = DoubleList< DoubleList< size_t > >;
  void createIntList(DoubleList< size_t > &list, std::string &integerString, bool &isBigNumber);
  void processInput(DoubleList< size_t > &summaList, listOfList &resultList, listPair &allPairs);
  void inputPairs(listPair &allPairs, bool &isBigNumber);
  void outputListName(const listPair &allPairs);
  void outputLists(listOfList &resultList);
  void outputSumma(const bool &isBigNumber, DoubleList< size_t > &summaList);
}

#endif
