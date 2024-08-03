#ifndef SHAKERSORT_HPP
#define SHAKERSORT_HPP
#include <iterator>

namespace nikiforov
{
  template< typename T, typename Compare >
  void shakerSort(T begin, T end, Compare cmp)
  {
    bool swap = true;
    while (swap)
    {
      swap = false;
      for (auto it = begin; it != std::prev(end); ++it)
      {
        if (cmp(*std::next(it), *it))
        {
          std::iter_swap(it, std::next(it));
          swap = true;
        }
      }

      if (!swap) break;

      swap = false;
      for (auto it = std::prev(end); it != begin; --it)
      {
        if (cmp(*it, *std::prev(it)))
        {
          std::iter_swap(it, std::prev(it));
          swap = true;
        }
      }
    }
  }
}

#endif
