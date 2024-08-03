#ifndef SORTS_HPP
#define SORTS_HPP

#include <algorithm>
#include <list.hpp>
#include <iterator>
#include <forward_list>

namespace mihalchenko
{
  template < typename Iter, typename Compare >
  void quickSort(Iter begin, Iter end, Compare compare);

  template < typename Iter, typename Compare >
  Iter partOfQuickSort(Iter begin, Iter end, Compare compare);

  template < typename Iter, typename Compare >
  void mergeSort(Iter begin, Iter end, Compare compare);

  template < typename Iter, typename Compare >
  void merge(Iter begin, Iter center, Iter end, Compare compare);
}

template < typename Iter, typename Compare >
void mihalchenko::quickSort(Iter begin, Iter end, Compare compare)
{
  if (std::distance(begin, end) <= 1)
  {
    return;
  }
  Iter temp_pos = partOfQuickSort(begin, end, compare);
  quickSort(begin, temp_pos, compare);
  quickSort(++temp_pos, end, compare);
}

template < typename Iter, typename Compare >
Iter mihalchenko::partOfQuickSort(Iter begin, Iter end, Compare compare)
{
  auto temp = *begin;
  Iter temp_pos = begin;
  ++begin;
  Iter part_iter = temp_pos;
  for (Iter iter = begin; iter != end; ++iter)
  {
    if (compare(*iter, temp))
    {
      ++part_iter;
      std::iter_swap(part_iter, iter);
    }
  }
  std::iter_swap(temp_pos, part_iter);
  return part_iter;
}

template < typename Iter, typename Compare >
void mihalchenko::mergeSort(Iter begin, Iter end, Compare compare)
{
  size_t size = std::distance(begin, end);
  if (size < 2)
  {
    return;
  }
  Iter center = begin;
  for (size_t i = 0; i < 0.5 * size; i++)
  {
    center++;
  }
  mergeSort(begin, center, compare);
  mergeSort(center, end, compare);
  merge(begin, center, end, compare);
}

template < typename Iter, typename Compare >
void mihalchenko::merge(Iter begin, Iter center, Iter end, Compare compare)
{
  mihalchenko::List< typename std::iterator_traits< Iter >::value_type > vector;
  Iter first = begin;
  Iter second = center;
  while (first != center && second != end)
  {
    if (compare(*first, *second))
    {
      vector.push_front(std::move(*first));
      ++first;
    }
    else
    {
      vector.push_front(std::move(*second));
      ++second;
    }
  }
  while (first != center)
  {
    vector.push_front(std::move(*first));
    ++first;
  }
  while (second != end)
  {
    vector.push_front(std::move(*second));
    ++second;
  }
  vector.reverse();
  auto temp_iter = vector.begin();
  for (Iter it = begin; it != end; ++it)
  {
    *it = std::move(*temp_iter);
    ++temp_iter;
  }
}

#endif
