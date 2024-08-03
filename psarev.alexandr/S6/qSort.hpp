#ifndef Q_SORT_HPP
#define Q_SORT_HPP
#include <iterator>
#include <algorithm>

namespace psarev
{
  template< typename Iter, typename Compare >
  void sortQ(Iter begin, Iter end, Compare compare);

  template< typename Iter, typename Compare >
  Iter partition(Iter begin, Iter end, Compare compare);
}

template<typename Iter, typename Compare>
void psarev::sortQ(Iter begin, Iter end, Compare compare) {
  if (begin == end || std::next(begin) == end) return;

  Iter pivot = psarev::partition(begin, end, compare);
  sortQ(begin, pivot, compare);

  if (pivot != end)
  {
    sortQ(std::next(pivot), end, compare);
  }
}

template< typename Iter, typename Compare >
Iter psarev::partition(Iter begin, Iter end, Compare compare) {
  auto pivotValue = *begin;
  Iter pivotPos = begin;
  Iter iter = std::next(begin);

  for (; iter != end; ++iter)
  {
    if (compare(*iter, pivotValue))
    {
      pivotPos = std::next(pivotPos);
      std::iter_swap(iter, pivotPos);
    }
  }
  std::iter_swap(begin, pivotPos);
  return pivotPos;
}

#endif
