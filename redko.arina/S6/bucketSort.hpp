#ifndef BUCKETSORT_HPP
#define BUCKETSORT_HPP
#include <algorithm>
#include <vector>

namespace redko
{
  template < typename It, typename Comparator >
  void sortBucket(It first, It last, Comparator comp)
  {
    auto minmax = std::minmax_element(first, last, comp);
    const int num = 5;
    if (std::distance(first, last) > 1 && *(minmax.first) != *(minmax.second))
    {
      int range = std::abs(*(minmax.second) - *(minmax.first));
      std::vector< typename It::value_type > buckets[num];
      for (It curr = first; curr != last; ++curr)
      {
        int index = std::abs((*curr - *(minmax.first)) * num / (1 + range));
        buckets[index].push_back(*curr);
      }
      for (int i = 0; i < num; ++i)
      {
        sortBucket(buckets[i].begin(), buckets[i].end(), comp);
        for (auto j = buckets[i].begin(); j != buckets[i].end(); ++j)
        {
          *first = *j;
          ++first;
        }
      }
    }
  }
}

#endif
