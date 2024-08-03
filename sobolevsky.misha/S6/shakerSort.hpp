#ifndef SHAKERSORT_HPP
#define SHAKERSORT_HPP

#include <algorithm>
#include <iostream>

namespace sobolevsky
{
  template < typename Iterator, typename Comparator >
  void shakerSort(Iterator begin, Iterator end, Comparator comp)
  {
    end--;
    while (begin != end)
    {
      Iterator left = begin;
      Iterator right = end;

      while (left != right)
      {
        if (comp(*std::next(left), *left))
        {
          std::iter_swap(left, std::next(left));
          end = left;
        }
        left++;
      }

      if (left == begin)
      {
        break;
      }

      while (right != begin)
      {
        if (comp(*right, *std::prev(right)))
        {
          std::iter_swap(right, std::prev(right));
        }
        right--;
      }

      begin++;
    }
  }
}

#endif
