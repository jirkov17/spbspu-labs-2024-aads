#ifndef MAIN_UTILS_HPP
#define MAIN_UTILS_HPP

#include "list.hpp"

namespace miheev
{
  using SI_pair = std::pair< std::string, miheev::List< size_t > >;
  using ListIter = miheev::List<size_t>::Iterator;
  template <class T>
  void pPrint(T* arr, size_t size);
  std::pair<SI_pair*, size_t> expandArr(SI_pair* pairs, size_t size);
  SI_pair getSIPair(std::istream& stream);
  ListIter* getNonEmptyIters(SI_pair* pairs, size_t size);
  size_t maxListSize(List< size_t >* lists, size_t size);
  size_t calcMaxListSize(SI_pair* pairs, size_t unusedIndex);
  bool calcSumsArr(SI_pair* pairs, size_t unusedIndex, size_t* accumulator);
  void printSums(size_t* sums, size_t size, bool isOverflow);
}

template <class T>
void miheev::pPrint(T* arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    std::cout << arr[i];
    if (i < size - 1)
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
}

#endif
