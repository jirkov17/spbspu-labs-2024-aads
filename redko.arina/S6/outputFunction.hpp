#ifndef OUTPUTFUNCTIONS_HPP
#define OUTPUTFUNCTIONS_HPP
#include <ostream>
#include <iomanip>
#include <limits>
#include <deque>
#include <list>
#include "list.hpp"
#include "bucketSort.hpp"
#include "quickSort.hpp"

namespace redko
{
  template< typename It >
  void printSorted(std::ostream & out, It first, It last)
  {
    while (first != last)
    {
      out << *first;
      out << (++first == last ? '\n' : ' ');
    }
  }

  void fillRandom(List< int > & list, int size)
  {
    for (auto i = 0; i < size; ++i)
    {
      list.pushBack((rand() - rand()) % 10000);
    }
  }

  void fillRandom(List< double > & list, int size)
  {
    for (auto i = 0; i < size; ++i)
    {
      list.pushBack((rand() - rand()) % 10000 + (double(rand()) / rand()));
    }
  }

  template< typename T, typename Compare >
  void sortData(std::ostream & out, int size, Compare comp)
  {
    srand(time(0));
    List< T > forwardList{};
    fillRandom(forwardList, size);

    std::list< T > firstList(size);
    std::copy_n(forwardList.cbegin(), size, firstList.begin());
    std::list< T > secondList(size);
    std::copy_n(forwardList.cbegin(), size, secondList.begin());
    std::deque< T > firstDeque(size);
    std::copy_n(forwardList.cbegin(), size, firstDeque.begin());
    std::deque< T > secondDeque(size);
    std::copy_n(forwardList.cbegin(), size, secondDeque.begin());
    std::deque< T > thirdDeque(size);
    std::copy_n(forwardList.cbegin(), size, thirdDeque.begin());

    printSorted(out, forwardList.begin(), forwardList.end());

    sortBucket(forwardList.begin(), forwardList.end(), comp);
    sortBucket(firstList.begin(), firstList.end(), comp);
    sortQuick(secondList.begin(), secondList.end(), comp);
    sortBucket(firstDeque.begin(), firstDeque.end(), comp);
    sortQuick(secondDeque.begin(), secondDeque.end(), comp);
    std::sort(thirdDeque.begin(), thirdDeque.end(), comp);

    printSorted(out, forwardList.begin(), forwardList.end());
    printSorted(out, firstList.begin(), firstList.end());
    printSorted(out, secondList.begin(), secondList.end());
    printSorted(out, firstDeque.begin(), firstDeque.end());
    printSorted(out, secondDeque.begin(), secondDeque.end());
    printSorted(out, thirdDeque.begin(), thirdDeque.end());
  }
}

#endif
