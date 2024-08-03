#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <forward_list>
#include <iostream>
#include <iterator>
#include "doublelist.hpp"
#include "BinarySearchTree.hpp"

namespace kovshikov
{
  void getRandom(DoubleList< int >& list, std::forward_list< int >& forward, std::deque< int >& deque, size_t size);
  void getRandom(DoubleList< float >& list, std::forward_list< float >& forward, std::deque< float >& deque, size_t size);

  template< typename Container >
  void printConteiner(const Container& container, std::ostream& out);

  template<class InputIterator, class OutputIterator>
  OutputIterator myCopy(InputIterator first, InputIterator last, OutputIterator result);
}

void kovshikov::getRandom(DoubleList< int >& list, std::forward_list< int >& forward, std::deque< int >& deque, size_t size)
{
  std::srand(0);
  for(size_t i = 0; i < size; i++)
  {
    list.push_front(std::rand() % 1000);
  }
  myCopy(list.begin(), list.end(), std::front_inserter(deque));
  myCopy(list.begin(), list.end(), std::front_inserter(forward));
}

template<class InputIterator, class OutputIterator>
OutputIterator kovshikov::myCopy(InputIterator first, InputIterator last, OutputIterator result)
{
  while (first!=last)
  {
    *result = *first;
    ++result; ++first;
  }
  return result;
}

void kovshikov::getRandom(DoubleList< float >& list, std::forward_list< float >& forward, std::deque< float >& deque, size_t size)
{
  std::srand(0);
  for(size_t i = 0; i < size; i++)
  {
    float element = static_cast< float >(std::rand() % 1000) / static_cast< float >(std::rand() % 1000);
    list.push_front(element);
  }
  myCopy(list.begin(), list.end(), std::front_inserter(deque));
  myCopy(list.begin(), list.end(), std::front_inserter(forward));
}

template< typename Container >
void kovshikov::printConteiner(const Container& container, std::ostream& out)
{
  auto begin = container.begin();
  auto end = container.end();
  auto next = begin;
  while(begin != end)
  {
    next++;
    if(next == end)
    {
      out << *begin << "\n";
    }
    else
    {
      out << *begin << " ";
    }
    begin++;
  }
}

#endif
