#ifndef SORTS_HPP
#define SORTS_HPP

#include <iterator>

namespace ponomarev
{
  template < typename Iterator, typename Comparator >
  void sortInsertion(Iterator begin, Iterator end, Comparator comp)
  {
    for (auto it = begin; it != end; ++it)
    {
      auto current = *it;
      auto pos = it;
      while (pos != begin && comp(current, *std::prev(pos)))
      {
        *pos = *std::prev(pos);
        if (pos != begin) {
          --pos;
        }
      }

      *pos = current;
    }
  }

  template < typename Iterator, typename Comparator >
  void sortShaker(Iterator begin, Iterator end, Comparator comp)
  {
    Iterator left = begin;
    Iterator right = end;
    right--;
    bool sortFlag = true;

    while (sortFlag)
    {
      sortFlag = false;

      for (auto it = left; it != right; it++)
      {
        if (comp(*std::next(it), *it))
        {
          std::iter_swap(it, std::next(it));
          sortFlag = true;
        }
      }

      for (auto it = right; it != left; it--)
      {
        if (comp(*it, *std::prev(it)))
        {
          std::iter_swap(it, std::prev(it));
          sortFlag = true;
        }
      }

      left++;
      right--;
    }
  }
}

#endif
