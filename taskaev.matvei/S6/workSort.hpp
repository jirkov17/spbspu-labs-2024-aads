#ifndef WORKSORT_HPP
#define WORKSORT_HPP
#include <iostream>
#include <deque>
#include <forward_list>
#include <iomanip>
#include <list>
#include <string>
#include <random>
#include <algorithm>
#include "sortFunctions.hpp"


namespace taskaev
{
  template < typename Iterators >
  void print(Iterators& iter, std::ostream& out)
  {
    auto it = iter.begin();
    out << *it;
    it++;
    while (it != iter.end())
    {
      out << " ";
      out << *it;
      it++;
    }
    out << "\n";
  }

  template <typename T >
  void generateData(size_t size, std::string types, std::forward_list< T >& myList)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (size_t i = 0; i < size; ++i)
    {
      if (types == "ints")
      {
        std::uniform_int_distribution< int > dis(-10000, 10000);
        int val = dis(gen);
        myList.push_front(val);
      }
      else if (types == "floats")
      {
        std::uniform_real_distribution< float > dis(0.0f, 99.9f);
        float val = dis(gen);
        myList.push_front(val);
      }
    }
  }

  template< typename T, typename Comparator >
  void workSortings(std::ostream& out, std::string types, size_t size, Comparator comp)
  {
    std::forward_list< T > myList;
    generateData(size, types, myList);
    print(myList, out);
    std::deque< T > queueOne;
    std::deque< T > queueTwo;
    std::list< T > listOne;
    std::list< T > listTwo;
    std::copy(myList.begin(), myList.end(), std::back_inserter(queueOne));
    std::copy(myList.begin(), myList.end(), std::back_inserter(queueTwo));
    std::copy(myList.begin(), myList.end(), std::back_inserter(listOne));
    std::copy(myList.begin(), myList.end(), std::back_inserter(listTwo));

    Shaker(queueOne.begin(), queueOne.end(), comp);
    print(queueOne, out);

    Shaker(listOne.begin(), listOne.end(), comp);
    print(listOne, out);

    Selection(queueTwo.begin(), queueTwo.end(), comp);
    print(queueTwo, out);

    Selection(listTwo.begin(), listTwo.end(), comp);
    print(listTwo, out);

    Selection(myList.begin(), myList.end(), comp);
    print(myList, out);
    print(myList, out);
  }
}

#endif

