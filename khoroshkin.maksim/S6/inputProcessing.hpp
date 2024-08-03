#ifndef INPUTPROCESSING_HPP
#define INPUTPROCESSING_HPP

#include <iostream>
#include <deque>
#include <algorithm>
#include <iomanip>
#include <list>
#include "list.hpp"

namespace khoroshkin
{
  template< typename T >
  std::ostream & outGothContainer(std::ostream & out, const T & container);

  template< typename T, typename Compare >
  void sortData(std::ostream & stream, size_t size, Compare comp);

  void fillGothRand(size_t size, List< int > & frwdList, std::list< int > & lst, std::deque< int > & deq);
  void fillGothRand(size_t size, List< double > & frwdList, std::list< double > & lst, std::deque< double > & deq);
}

template< typename T >
std::ostream & khoroshkin::outGothContainer(std::ostream & out, const T & container)
{
  for (auto it = container.begin(); it != container.end(); it++)
  {
    out << std::fixed << std::setprecision(1) << *it;
    out << ((std::next(it) == container.end()) ? "\n" : " ");
  }
  return out;
}

template< typename T, typename Compare >
void khoroshkin::sortData(std::ostream & stream, size_t size, Compare comp)
{
  List< T > forwardList;
  std::list< T > list;
  std::deque< T > deque;

  fillGothRand(size, forwardList, list, deque);

  outGothContainer(stream, forwardList);
  timSort(forwardList.begin(), forwardList.end(), comp);
  outGothContainer(stream, forwardList);

  shellSort(list.begin(), list.end(), comp);
  outGothContainer(stream, list);
  timSort(list.begin(), list.end(), comp);
  outGothContainer(stream, list);

  shellSort(deque.begin(), deque.end(), comp);
  outGothContainer(stream, deque);
  timSort(deque.begin(), deque.end(), comp);
  outGothContainer(stream, deque);
  std::sort(deque.begin(), deque.end(), comp);
  outGothContainer(stream, deque);
}

void khoroshkin::fillGothRand(size_t size, List< int > & frwdList, std::list< int > & lst, std::deque< int > & deq)
{
  for (size_t i = 0; i < size; ++i)
  {
    frwdList.push_back(rand() % 100);
  }
  std::copy(frwdList.begin(), frwdList.end(), std::back_inserter(lst));
  std::copy(frwdList.begin(), frwdList.end(), std::back_inserter(deq));
}

void khoroshkin::fillGothRand(size_t size, List< double > & frwdList, std::list< double > & lst, std::deque< double > & deq)
{
  for (size_t i = 0; i < size; ++i)
  {
    frwdList.push_back(double(rand() % 1000) / double(rand() % 100));
  }
  std::copy(frwdList.begin(), frwdList.end(), std::back_inserter(lst));
  std::copy(frwdList.begin(), frwdList.end(), std::back_inserter(deq));
}

#endif
