#ifndef SORT_HPP
#define SORT_HPP

#include <algorithm>
#include <iterator>
#include <vector>
#include <stack>

namespace reznikova
{
  template< typename Iterator, typename Comparator >
  void qsort(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Comparator >
Iterator partition(Iterator first, Iterator last, Comparator cmp);
  template< typename Iterator, typename Comparator >
  void shaker(Iterator first, Iterator last, Comparator cmp);
}

template<typename Iterator, typename Comparator>
Iterator reznikova::partition(Iterator first, Iterator last, Comparator cmp)
{
  auto pivot = *first;
  Iterator pivotPos = first;
  ++first;
  Iterator partitionIter = pivotPos;
  for (Iterator iter = first; iter != last; ++iter)
  {
    if (cmp(*iter, pivot))
    {
      ++partitionIter;
      std::iter_swap(partitionIter, iter);
    }
  }
  std::iter_swap(pivotPos, partitionIter);
  return partitionIter;
}

template<typename Iterator, typename Comparator>
void reznikova::qsort(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last || std::next(first) == last)
  {
    return;
  }
  Iterator pivotPos = reznikova::partition(first, last, cmp);
  qsort(first, pivotPos, cmp);
  qsort(std::next(pivotPos), last, cmp);
}

template<typename Iterator, typename Comparator>
void reznikova::shaker(Iterator first, Iterator last, Comparator cmp)
{
  if (first == last || std::next(first) == last)
  {
    return;
  }
  Iterator begin = first;
  Iterator end = first;
  while (std::next(end) != last)
  {
    ++end;
  }
  while (true)
  {
    bool swapped = false;
    for (Iterator it = begin; it != end; ++it)
    {
      Iterator next = std::next(it);
      if (cmp(*next, *it))
      {
        std::iter_swap(it, next);
        swapped = true;
      }
    }
    if (!swapped)
    {
      break;
    }
    if (begin == end)
    {
      break;
    }
    --end;
    swapped = false;
    for (Iterator it = end; it != begin; --it)
    {
      Iterator prev = std::prev(it);
      if (cmp(*it, *prev))
      {
        std::iter_swap(it, prev);
        swapped = true;
      }
    }
    if (!swapped) break;
    if (begin == end)
    {
      break;
    }
    ++begin;
  }
}

#endif
