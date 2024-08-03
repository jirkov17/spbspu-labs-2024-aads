#ifndef DATAPROCESSING_HPP
#define DATAPROCESSING_HPP
#include <string>
#include <list>
#include <random>
#include <deque>
#include "List.hpp"
#include "sorts.hpp"

namespace sukacheva
{
  template< typename T >
  void generateRandom(size_t size, std::string type, List< T >& list, std::list< T >& bidList, std::deque< T >& queue)
  {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (size_t i = 0; i < size; ++i)
    {
      if (type == "ints")
      {
        std::uniform_int_distribution< int > dis(-10000, 10000);
        int value = dis(gen);
        list.pushBack(value);
        bidList.push_back(value);
        queue.push_back(value);
      }
      else if (type == "floats")
      {
        std::uniform_real_distribution< float > dis(0.0f, 99.9f);
        float value = dis(gen);
        list.pushBack(value);
        bidList.push_back(value);
        queue.push_back(value);
      }
    }
  }

  template< typename Iterator >
  void printCont(Iterator begin, Iterator end, std::ostream& out)
  {
    out << *begin;
    begin++;
    while (begin != end)
    {
      out << ' ' << *begin;
      begin++;
    }
    out << "\n";
  }

  template< typename T, typename Comparator >
  void sortConts(std::string type, size_t size, std::ostream& out, Comparator cmp)
  {
    List< T > forwardList;
    std::list< T > list;
    std::deque< T > deque;
    generateRandom(size, type, forwardList, list, deque);
    printCont(forwardList.begin(), forwardList.end(), out);

    bucketSort(forwardList.begin(), forwardList.end(), cmp);
    printCont(forwardList.begin(), forwardList.end(), out);

    bucketSort(list.begin(), list.end(), cmp);
    printCont(list.begin(), list.end(), out);
    shellSort(list.begin(), list.end(), cmp);
    printCont(list.begin(), list.end(), out);

    bucketSort(deque.begin(), deque.end(), cmp);
    printCont(deque.begin(), deque.end(), out);
    shellSort(deque.begin(), deque.end(), cmp);
    printCont(deque.begin(), deque.end(), out);
    std::sort(deque.begin(), deque.end(), cmp);
    printCont(deque.begin(), deque.end(), out);
  }
}

#endif
