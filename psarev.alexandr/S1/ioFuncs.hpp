#ifndef IO_FUNCS
#define IO_FUNCS
#include <iostream>
#include <limits>
#include <utility>
#include <algorithm>
#include "list.hpp"
#include "divideFuncs.hpp"

using depot_t = psarev::List< std::pair< std::string, psarev::List< unsigned long long > > >;

namespace psarev
{
  template< typename T >
  void inputData(depot_t& lines, size_t& maxDigits);

  template< typename T >
  void outOrds(depot_t& lines);

  template< typename T >
  List< T > outDigits(depot_t& lines, size_t& maxDigits, bool& isOF);

  template< typename T >
  void outSums(List< T >& sums);
}

template<typename T>
void psarev::inputData(depot_t& lines, size_t& maxDigits)
{
  depot_t::Iterator iterLine;
  std::string line = "";

  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string ord = psarev::getOrd(line);
      std::pair< std::string, psarev::List< unsigned long long > > pair = { ord, {} };
      lines.pushBack(pair);
      iterLine = lines.begin();
      for (size_t i = 0; i < (lines.getSize() - 1); i++)
      {
        iterLine++;
      }
      size_t cntDigits = 0;
      while (line.size() != 0)
      {
        unsigned long long digit = psarev::getDigit(line);
        (*iterLine).second.pushBack(digit);
        cntDigits++;
      }
      maxDigits = std::max(maxDigits, cntDigits);
    }
  }
}

template< typename T >
void psarev::outOrds(depot_t& lines)
{
  depot_t::Iterator iterLine = lines.begin();
  for (size_t i = 0; i < lines.getSize(); i++)
  {
    std::cout << (*iterLine).first;
    iterLine++;
    if (i < (lines.getSize() - 1))
    {
      std::cout << ' ';
    }
    else
    {
      std::cout << '\n';
    }
  }
}

template< typename T >
psarev::List< T > psarev::outDigits(depot_t& lines, size_t& maxDigits, bool& isOF)
{
  unsigned long long maxUll = std::numeric_limits< unsigned long long >::max();
  depot_t::Iterator iterLine = lines.begin();
  typename List< T >::Iterator iterDig;
  List< T > sums;
  T curSum = 0;
  for (size_t i = 0; i < maxDigits; i++)
  {
    curSum = 0;
    iterLine = lines.begin();
    for (iterLine = lines.begin(); iterLine != lines.end(); iterLine++)
    {
      iterDig = (*iterLine).second.begin();
      if ((*iterLine).second.getSize() > i)
      {
        iterDig = i != 0 ? (iterDig + i) : iterDig;
        curSum != 0 ? std::cout << ' ' << *iterDig : std::cout << *iterDig;
        *iterDig > (maxUll - curSum) ? isOF = true : curSum += *iterDig;
      }
    }
    sums.pushBack(curSum);
    std::cout << '\n';
  }
  return sums;
}

template< typename T >
void psarev::outSums(List< T >& sums)
{
  if (sums.empty())
  {
    std::cout << 0;
  }
  else
  {
    typename psarev::List< T >::Iterator iterSums = sums.begin();
    for (size_t i = 0; i < sums.getSize(); i++)
    {
      if (i != 0)
      {
        std::cout << ' ';
      }
      std::cout << *iterSums;
      iterSums++;
    }
  }
  std::cout << '\n';
}

#endif
