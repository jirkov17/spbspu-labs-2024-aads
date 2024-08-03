#ifndef OUTPUT_FUNCTIONS_HPP
#define OUTPUT_FUNCTIONS_HPP

#include <iostream>
#include <utility>
#include "list.hpp"
#include <limits>

using pair = ponomarev::List< std::pair< std::string, ponomarev::List< unsigned long long > > >;

namespace ponomarev
{
  template < typename T >
  List< T > outputNums(pair& data, size_t& maxLenSeq, bool& overflowCheck);
  template < typename T >
  void outputSums(List< T >& sums);
}

template < typename T >
ponomarev::List< T > ponomarev::outputNums(pair& data, size_t& maxLenSeq, bool& overflowCheck)
{
  pair::Iterator seqIterator = data.begin();
  typename List< T >::Iterator numIterator;
  List< T > sums;
  T lineSum = 0;
  for (size_t i = 0; i < maxLenSeq; i++)
  {
    lineSum = 0;
    seqIterator = data.begin();
    for (seqIterator = data.begin(); seqIterator != data.end(); seqIterator++)
    {
      numIterator = (*seqIterator).second.begin();
      if ((*seqIterator).second.getSize() > i)
      {
        numIterator = i != 0 ? (numIterator + i) : numIterator;
        lineSum != 0 ? std::cout << ' ' << *numIterator : std::cout << *numIterator;
        if (*numIterator > (std::numeric_limits< unsigned long long >::max() - lineSum))
        {
          overflowCheck = true;
          break;
        }
        else
        {
          lineSum += *numIterator;
        }
      }
    }
    sums.pushBack(lineSum);
    std::cout << '\n';
  }
  return sums;
}

template < typename T >
void ponomarev::outputSums(List< T >& sums)
{
  if (sums.isEmpty())
  {
    std::cout << 0;
  }
  else
  {
    typename ponomarev::List< T >::Iterator iteratorSums = sums.begin();
    for (size_t i = 0; i < sums.getSize(); i++)
    {
      if (i != 0)
      {
        std::cout << ' ';
      }
      std::cout << *iteratorSums;
      iteratorSums++;
    }
  }
  std::cout << '\n';
}

#endif
