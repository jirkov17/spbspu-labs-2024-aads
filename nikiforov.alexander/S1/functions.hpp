#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

namespace nikiforov
{
  template < typename T >
  using list_t = List< std::pair< std::string, List< T > > >;

  template < typename T >
  size_t outputName_(List< std::pair< std::string, List< T > > >& seqsPair);

  template < typename T >
  void outputSeqs_(List< std::pair< std::string, List< T > > >& seqsPair, List< T >& listSumm, size_t maxSize);

  template < typename T >
  void outputSumm_(List< T >& listSumm);

  size_t max(const size_t first_param, const size_t second_param);
}

template< typename T >
size_t nikiforov::outputName_(List< std::pair< std::string, List< T > > >& seqsPair)
{
  List< std::pair< std::string, List< unsigned long long > > >::Iterator iterSeqsPair = seqsPair.begin();
  size_t countNames = seqsPair.getSize();
  size_t maxSize = 0;
  for (iterSeqsPair = seqsPair.begin(); iterSeqsPair != seqsPair.end(); ++iterSeqsPair)
  {
    if (countNames == 1)
    {
      std::cout << iterSeqsPair->first << "\n";
    }
    else
    {
      std::cout << iterSeqsPair->first << " ";
    }
    countNames--;
    maxSize = max(maxSize, (*iterSeqsPair).second.getSize());
  }
  return maxSize;
}

template< typename T >
void nikiforov::outputSeqs_(List< std::pair< std::string, List< T > > >& seqsPair, List< T >& listSumm, size_t maxSize)
{
  List< std::pair< std::string, List< unsigned long long > > >::ConstIterator iterSeqsPair = seqsPair.cbegin();
  List< unsigned long long >::ConstIterator iterList = (*iterSeqsPair).second.cbegin();
  List< unsigned long long >::ConstIterator iterListEnd = (*iterSeqsPair).second.cend();
  size_t countInSeq = 0;
  unsigned long long summ = 0;
  bool firstElem = false;
  bool overflow = false;

  while (countInSeq < maxSize)
  {
    firstElem = false;
    for (iterSeqsPair = seqsPair.cbegin(); iterSeqsPair != seqsPair.cend(); ++iterSeqsPair)
    {
      iterList = (*iterSeqsPair).second.begin();
      for (size_t i = 0; i < countInSeq; i++)
      {
        if (iterList != iterListEnd)
        {
          iterList++;
        }
      }
      if (iterList != iterListEnd)
      {
        firstElem ? std::cout << " " << *iterList : std::cout << *iterList;
        firstElem = true;
        if ((std::numeric_limits< unsigned long long >::max() - summ) > *iterList)
        {
          summ += *iterList;
        }
        else
        {
          overflow = true;
        }
      }
    }
    std::cout << "\n";
    countInSeq++;
    listSumm.push_back(summ);
    summ = 0;
  }
  if (overflow)
  {
    throw std::overflow_error("Error: overflow!");
  }
}

template< typename T >
void nikiforov::outputSumm_(List< T >& listSumm)
{
  List< unsigned long long >::Iterator iterListSummEnd = listSumm.end();
  size_t count = 0;
  for (List< unsigned long long >::Iterator iterListSumm = listSumm.begin(); iterListSumm != iterListSummEnd; ++iterListSumm)
  {
    count++;
    listSumm.getSize() == count ? std::cout << *iterListSumm : std::cout << *iterListSumm << " ";
  }
  std::cout << "\n";
}

size_t nikiforov::max(const size_t first_param, const size_t second_param)
{
  return first_param > second_param ? first_param : second_param;
}

#endif
