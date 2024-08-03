#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include <forward_list>
#include <algorithm>
#include <iterator>

namespace nikiforov
{
  template< typename T >
  T findMiddle(T begin, T end)
  {
    T fast = begin;
    T slow = begin;
    while (fast != end && std::next(fast) != end)
    {
      fast = std::next(fast);
      fast = std::next(fast);
      slow = std::next(slow);
    }
    return slow;
  }

  template< typename T, typename Compare >
  void merge(T begin, T mid, T end, Compare cmp)
  {
    std::forward_list<typename T::value_type> temp;
    auto it1 = begin;
    auto it2 = mid;
    while (it1 != mid && it2 != end)
    {
      if (cmp(*it1, *it2))
      {
        temp.push_front(std::move(*it1));
        it1 = std::next(it1);
      }
      else
      {
        temp.push_front(std::move(*it2));
        it2 = std::next(it2);
      }
    }

    while (it1 != mid)
    {
      temp.push_front(std::move(*it1));
      it1 = std::next(it1);
    }

    while (it2 != end)
    {
      temp.push_front(std::move(*it2));
      it2 = std::next(it2);
    }

    temp.reverse();
    auto it_temp = temp.begin();
    for (auto it = begin; it != end; ++it)
    {
      *it = std::move(*it_temp);
      it_temp = std::next(it_temp);
    }
  }

  template<typename T, typename Compare>
  void mergeSort(T begin, T end, Compare cmp)
  {
    if (begin == end || std::next(begin) == end)
    {
      return;
    }
    T mid = findMiddle(begin, end);
    mergeSort(begin, mid, cmp);
    mergeSort(mid, end, cmp);
    merge(begin, mid, end, cmp);
  }
}

#endif
