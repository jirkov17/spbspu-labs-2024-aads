#ifndef FUNCSSORT_HPP
#define FUNCSSORT_HPP
#include <iomanip>
#include <deque>
#include <list>
#include <list.hpp>
#include "mergeSort.hpp"
#include "shakerSort.hpp"

namespace nikiforov
{
  void fillLists(List< int >& forwardList, std::list< int >& list, std::deque< int >& deque, size_t size);
  void fillLists(List< double >& forwardList, std::list< double >& list, std::deque< double >& deque, size_t size);

  template< typename T, typename Compare >
  void makeSorted(std::ostream& out, size_t size, Compare compare);

  template< typename T >
  void outputSequence(const T& depot, std::ostream& out);

  std::ostream& errorMessages(std::ostream& out);
}

void nikiforov::fillLists(List< int >& forwardList, std::list< int >& list, std::deque< int >& deque, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    forwardList.push_back(rand() % 100);
  }

  std::copy(forwardList.begin(), forwardList.end(), std::front_inserter(list));
  std::copy(forwardList.begin(), forwardList.end(), std::back_inserter(deque));
}

void nikiforov::fillLists(List< double >& forwardList, std::list< double >& list, std::deque< double >& deque, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    forwardList.push_back(double(rand() % 1000) / double(rand() % 100));
  }

  std::copy(forwardList.begin(), forwardList.end(), std::front_inserter(list));
  std::copy(forwardList.begin(), forwardList.end(), std::back_inserter(deque));
}

template< typename T >
void nikiforov::outputSequence(const T& depot, std::ostream& out)
{
  for (auto iter = depot.begin(); iter != depot.end(); iter++)
  {
    out << std::fixed << std::setprecision(1) << *iter;
    if (std::next(iter) != depot.end())
    {
      out << " ";
    }
  }
  out << "\n";
}

template< typename T, typename Compare >
void nikiforov::makeSorted(std::ostream& out, size_t size, Compare cmp)
{
  List< T > forwardList;
  std::list< T > list;
  std::deque< T > deque;

  fillLists(forwardList, list, deque, size);

  outputSequence(forwardList, out);
  mergeSort(forwardList.begin(), forwardList.end(), cmp);
  outputSequence(forwardList, out);

  mergeSort(list.begin(), list.end(), cmp);
  outputSequence(list, out);
  shakerSort(list.begin(), list.end(), cmp);
  outputSequence(list, out);

  mergeSort(deque.begin(), deque.end(), cmp);
  outputSequence(deque, out);
  shakerSort(deque.begin(), deque.end(), cmp);
  outputSequence(deque, out);
  outputSequence(deque, out);
}

std::ostream& nikiforov::errorMessages(std::ostream& out)
{
  return out << "<ERROR>\n";
}

#endif
