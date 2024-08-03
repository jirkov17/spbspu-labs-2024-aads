#ifndef SORTFUNCTIONS_HPP
#define SORTFUNCTIONS_HPP
#include <iostream>
#include <algorithm>

namespace taskaev
{
  template <typename Iterator, typename Comparator >
  void Shaker(Iterator begin, Iterator end, Comparator comp)
  {
    if (begin == end || std::next(begin) == end)
    {
      return;
    }
    Iterator one = begin;
    Iterator two = begin;
    while (std::next(two) != end)
    {
      ++two;
    }
    while (true)
    {
      bool flag = false;
      Iterator iter = one;
      while (iter != two)
      {
        Iterator next = std::next(iter);
        if (comp(*next, *iter))
        {
          std::iter_swap(iter, next);
          flag = true;
        }
        iter++;
      }
      if (!flag)
      {
        break;
      }
      if (one == two)
      {
        break;
      }
      --two;
      flag = false;
      Iterator it = two;
      while (it != begin)
      {
        Iterator prev = std::prev(it);
        if (comp(*it, *prev))
        {
          std::iter_swap(it, prev);
          flag = true;
        }
        it--;
      }
      if (!flag)
      {
        break;
      }
      if (one == two)
      {
        break;
      }
      ++one;
    }
  }

  template <typename Iterator, typename Comparator >
  void Selection(Iterator begin, Iterator end, Comparator comp)
  {
    for (Iterator current = begin; current != end; current++)
    {
      Iterator next = current;
      next++;
      if (next == end)
      {
        return;
      }
      Iterator min = current;
      for (; next != end; next++)
      {
        if (comp(*next, *min))
        {
          min = next;
        }
      }
      if (*min != *current)
      {
        std::swap(*min, *current);
      }
    }
  }
}

#endif

