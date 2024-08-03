#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP
#include <iterator>

namespace redko
{
  template< typename It, typename Comparator >
  It part(It first, It last, Comparator comp)
  {
    --last;
    while (first != last)
    {
      if (comp(*first, *last))
      {
        --last;
      }
      else
      {
        if (std::next(first) != last)
        {
          std::iter_swap(last, std::next(first));
          std::iter_swap(first, std::next(first));
          ++first;
        }
        else
        {
          std::iter_swap(first, std::next(first));
          return ++first;
        }
      }
    }
    return first;
  }

  template< typename It, typename Comparator >
  void sortQuick(It first, It last, Comparator comp)
  {
    if (std::distance(first, last) > 1)
    {
      It split = part(first, last, comp);
      sortQuick(first, split, comp);
      if (split == first)
      {
        sortQuick(++first, last, comp);
      }
      else
      {
        sortQuick(split, last, comp);
      }
    }
  }
}

#endif
