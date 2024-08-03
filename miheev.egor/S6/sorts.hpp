#ifndef SORTS_HPP
#define SORTS_HPP

#include <functional>
#include <algorithm>
#include <iterator>

namespace miheev
{
  template < typename BidirectIt, typename Comparator >
  void shakeSort(BidirectIt start, BidirectIt finish, Comparator comp);

  template < typename BidirectIt, typename Comparator >
  void shellSort(BidirectIt start, BidirectIt finish, Comparator comp);
}

template < typename BidirectIt, typename Comparator >
void miheev::shakeSort(BidirectIt start, BidirectIt finish, Comparator comp)
{
  BidirectIt second = start;
  BidirectIt first = second++;

  bool swapped = false;
  do
  {
    swapped = false;
    while (second != finish)
    {
      if (comp(*second, *first))
      {
        std::iter_swap(first, second);
        swapped = true;
      }
      ++first;
      ++second;
    }
    while (first != start)
    {
      --first;
      --second;
      if (comp(*second, *first))
      {
        std::iter_swap(first, second);
        swapped = true;
      }
    }
  } while (swapped);
}

template < typename BidirectIt, typename Comparator >
void miheev::shellSort(BidirectIt start, BidirectIt finish, Comparator comp)
{
  long long dist = std::distance(start, finish);
  long long gap = 1;
  while (gap < dist / 2)
  {
    gap = 2 * gap + 1;
  }
  while (gap > 0)
  {
    for (auto i = std::next(start, gap); i != finish; i++)
    {
      for (auto j = i;
      std::distance(start, j) >= gap && comp(*j, *std::prev(j, gap)); j = std::prev(j, gap))
      {
        std::iter_swap(j, std::prev(j, gap));
      }
    }
    gap /= 2;
  }
}

#endif
