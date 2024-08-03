#include <deque>
#include <forward_list>
#include <list>
#include <iomanip>
#include <algorithm>
#include "sorts.hpp"

namespace ponomarev
{
  void inputRandomData(std::list< int > & list, int size)
  {
    for (int i = 0; i < size; ++i)
    {
      list.push_front((rand() % 1000));
    }
  }

  void inputRandomData(std::list< double > & list, int size)
  {
    for (int i = 0; i < size; ++i)
    {
      double firstNum = (double(rand() % 1000) - double(rand() % 1000));
      double secondNum = (double(rand() % 100) / double(rand() % 100));
      list.push_front(firstNum + secondNum);
    }
  }

  template< typename It >
  std::ostream & printData(std::ostream & out, It first, It last)
  {
    while (first != last)
    {
      out << std::fixed << std::setprecision(1) << *first;
      out << (++first == last ? '\n' : ' ');
    }
    return out;
  }

  template< typename T, typename Compare >
  void makeSort(std::ostream & out, int size, Compare comp)
  {
    std::forward_list< T > forwardList;
    std::list< T > firstList;
    std::list< T > secondList;
    inputRandomData(firstList, size);
    std::deque< T > firstDeque;
    std::deque< T > secondDeque;
    std::deque< T > thirdDeque;

    std::copy(firstList.begin(), firstList.end(), std::back_inserter(secondList));
    std::copy(firstList.begin(), firstList.end(), std::back_inserter(firstDeque));
    std::copy(firstList.begin(), firstList.end(), std::back_inserter(secondDeque));
    std::copy(firstList.begin(), firstList.end(), std::back_inserter(thirdDeque));
    std::copy(firstList.begin(), firstList.end(), std::front_inserter(forwardList));

    printData(out, firstList.begin(), firstList.end());
    sortShaker(firstList.begin(), firstList.end(), comp);
    sortShaker(firstDeque.begin(), firstDeque.end(), comp);
    sortInsertion(secondList.begin(), secondList.end(), comp);
    sortInsertion(secondDeque.begin(), secondDeque.end(), comp);
    forwardList.sort(comp);
    std::sort(thirdDeque.begin(), thirdDeque.end(), comp);

    printData(out, forwardList.begin(), forwardList.end());
    printData(out, firstList.begin(), firstList.end());
    printData(out, secondList.begin(), secondList.end());
    printData(out, firstDeque.begin(), firstDeque.end());
    printData(out, secondDeque.begin(), secondDeque.end());
    printData(out, thirdDeque.begin(), thirdDeque.end());
  }
}
