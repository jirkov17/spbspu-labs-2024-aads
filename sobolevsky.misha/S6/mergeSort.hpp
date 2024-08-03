#ifndef MERGERSORT_HPP
#define MERGERSORT_HPP

#include <cstddef>
#include <algorithm>
#include <iterator>
#include <list>

namespace sobolevsky
{
  template <typename Iterator, typename Comparator >
  void merge(Iterator begin, Iterator mid, Iterator end, Comparator comp)
  {
    std::list< typename Iterator::value_type > tempVec;
    Iterator left = begin;
    Iterator right = mid;

    while (left != mid && right != end)
    {
      if (comp(*left, *right))
      {
        tempVec.push_back(*left);
        left++;
      }
      else
      {
        tempVec.push_back(*right);
        right++;
      }
    }

    tempVec.insert(tempVec.end(), left, mid);
    tempVec.insert(tempVec.end(), right, end);

    std::copy(tempVec.begin(), tempVec.end(), begin);
  }

  template <typename Iterator, typename Comparator >
  void mergeSort(Iterator begin, Iterator end , Comparator comp)
  {
    int size = std::distance(begin, end);

    if (size <= 1)
    {
      return;
    }
    Iterator mid = begin;
    for (int i = 0; i < (size / 2); i++)
    {
      mid++;
    }
    mergeSort(begin, mid, comp);
    mergeSort(mid, end, comp);
    merge(begin, mid, end, comp);
  }
}

#endif
