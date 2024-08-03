#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "list.hpp"

namespace mihalchenko
{
  using mainList = mihalchenko::List< std::pair< std::string, mihalchenko::List< size_t > > >;
  using integerList = mihalchenko::List< size_t >;
  size_t printName(mainList &mixedList, size_t mixedListSize, size_t maxLenOfSecondList);
  size_t printSumDigit(integerList &tempIntList, size_t tempIntListSize);
  size_t printMixedList(mainList &mixedList, size_t mixedListSize, size_t numericView, bool &flgNewStr);
}

#endif
