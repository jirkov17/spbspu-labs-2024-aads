#ifndef IO_PROCESSING_HPP
#define IO_PROCESSING_HPP

#include <iostream>
#include <iomanip>
#include <deque>
#include <list>
#include <list.hpp>
#include <algorithm>
#include "sorts.hpp"

namespace miheev
{
  void printError(std::ostream&, std::string);
  template< typename Container >
  void printContainer(std::ostream&, const Container&);
  template< typename Printer, typename... PrinterArgs >
  void newLineWrapper(std::ostream&, Printer p, PrinterArgs... pArgs);

  void fillContainersWithRandom(std::deque< int >& deque, std::list< int >& bidirect, List< int > fwd, size_t amount);
  void fillContainersWithRandom(std::deque< double >& deque, std::list< double >& bidirect, List< double > fwd, size_t amount);

  template< typename T, typename Comparator >
  void testSorts(std::ostream&, size_t size,  Comparator comp);
}

void miheev::printError(std::ostream& out, std::string msg)
{
  out << "[ERROR]: " << msg << '\n';
}

template< typename Container >
void miheev::printContainer(std::ostream& out, const Container& container)
{
  out << std::fixed << std::setprecision(1);
  for (auto iter(container.cbegin()); iter != container.cend();)
  {
    out << *iter;
    if (++iter != container.cend())
    {
      out << ' ';
    }
  }
}
template< typename Printer, typename... PrinterArgs >
void miheev::newLineWrapper(std::ostream& out, Printer p, PrinterArgs... pArgs)
{
  p(out, pArgs...);
  out << '\n';
}

void miheev::fillContainersWithRandom(std::deque< int >& deque, std::list< int >& bidirect, List< int > fwd, size_t amount)
{
  for (size_t i = 0; i < amount; i++)
  {
    int random = rand() % 100;
    deque.push_back(random);
  }
  std::copy(deque.begin(), deque.end(), std::back_inserter(bidirect));
  copy(deque.begin(), deque.end(), std::back_inserter(fwd));
}

void miheev::fillContainersWithRandom(std::deque< double >& deque, std::list< double >& bidirect, List< double > fwd, size_t amount)
{
  for (size_t i = 0; i < amount; i++)
  {
    double random = static_cast< double >(rand() % 1000) / (rand() % 10);
    deque.push_back(random);
  }
  copy(deque.begin(), deque.end(), std::back_inserter(bidirect));
  copy(deque.begin(), deque.end(), std::back_inserter(fwd));
}

template< typename T, typename Comparator >
void miheev::testSorts(std::ostream& output, size_t size, Comparator comp)
{
  using Deque = std::deque< T >;
  using BiList = std::list< T >;
  using FwList = List< T >;

  BiList bidirect;
  Deque deque;
  FwList list;

  fillContainersWithRandom(deque, bidirect, list, size);

  newLineWrapper(output, printContainer< Deque >, deque);

  Deque dequeCopy;
  std::copy(deque.begin(), deque.end(), std::back_inserter(dequeCopy));
  Deque dequeCopy2;
  std::copy(deque.begin(), deque.end(), std::back_inserter(dequeCopy2));

  shakeSort(deque.begin(), deque.end(), comp);
  newLineWrapper(output, printContainer< Deque >, deque);
  shellSort(dequeCopy.begin(), dequeCopy.end(), comp);
  newLineWrapper(output, printContainer< Deque >, dequeCopy);

  BiList bidirectCopy;
  std::copy(bidirect.begin(), bidirect.end(), std::back_inserter(bidirectCopy));

  shakeSort(bidirect.begin(), bidirect.end(), comp);
  newLineWrapper(output, printContainer< BiList >, bidirect);
  shellSort(bidirectCopy.begin(), bidirectCopy.end(), comp);
  newLineWrapper(output, printContainer< BiList >, bidirectCopy);

  newLineWrapper(output, printContainer< BiList >, bidirectCopy);
  newLineWrapper(output, printContainer< BiList >, bidirectCopy);
}

#endif
