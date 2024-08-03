#ifndef SORTS_HPP
#define SORTS_HPP
#include <list>
#include <forward_list>
#include <deque>
#include <algorithm>
#include <iterator>
#include "output.hpp"
#include "random.hpp"

namespace zheleznyakov
{
  namespace sorts
  {
    template < typename Iterator, typename Comparator >
    void insertion(Iterator begin, Iterator end, Comparator cmp)
    {
      for (auto it = begin; it != end; ++it)
      {
        auto current = *it;
        auto pos = it;
        while (pos != begin && cmp(current, *std::prev(pos)))
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
    void oddEven(Iterator begin, Iterator end, Comparator cmp)
    {
      bool isSorted = false;

      while (!isSorted)
      {
        isSorted = true;
        Iterator next = std::next(begin);
        for (Iterator it = next; it != end && it != std::prev(end); std::advance(it, 2))
        {
          if (it != std::prev(end) && cmp(*std::next(it), *it))
          {
            std::iter_swap(it, std::next(it));
            isSorted = false;
          }
        }
        for (Iterator it = begin; it != end && it != std::prev(end); std::advance(it, 2))
        {
          if (cmp(*std::next(it), *it))
          {
            std::iter_swap(it, std::next(it));
            isSorted = false;
          }
        }
      }
    }
  }

  template< typename Type, typename Comparator >
  void executeSorts(std::ostream & out, size_t size, Comparator cmp)
  {
    std::list< Type > baseList;
    for (size_t i = 0; i < size; i++)
    {
      baseList.push_back(anarchy::randomDouble());
    }
    output::iterOut(baseList, out);

    std::list< Type > listForInsertion;
    std::copy(baseList.begin(), baseList.end(), std::back_inserter(listForInsertion));
    sorts::insertion(listForInsertion.begin(), listForInsertion.end(), cmp);
    output::iterOut(listForInsertion, out);

    std::list< Type > listForOddEven;
    std::copy(baseList.begin(), baseList.end(), std::back_inserter(listForOddEven));
    sorts::oddEven(listForOddEven.begin(), listForOddEven.end(), cmp);
    output::iterOut(listForOddEven, out);

    std::deque< Type > dequeForInsertion;
    std::copy(baseList.begin(), baseList.end(), std::back_inserter(dequeForInsertion));
    sorts::insertion(dequeForInsertion.begin(), dequeForInsertion.end(), cmp);
    output::iterOut(dequeForInsertion, out);

    std::deque< Type > dequeForOddEven;
    std::copy(baseList.begin(), baseList.end(), std::back_inserter(dequeForOddEven));
    sorts::oddEven(dequeForOddEven.begin(), dequeForOddEven.end(), cmp);
    output::iterOut(dequeForOddEven, out);

    std::deque< Type > dequeForSort;
    std::copy(baseList.begin(), baseList.end(), std::back_inserter(dequeForSort));
    std::sort(dequeForSort.begin(), dequeForSort.end(), cmp);
    output::iterOut(dequeForSort, out);

    std::forward_list< Type > fwdListForSort;
    std::copy(baseList.begin(), baseList.end(), std::front_inserter(fwdListForSort));
    fwdListForSort.sort(cmp);
    output::iterOut(fwdListForSort, out);
  }
}
#endif
