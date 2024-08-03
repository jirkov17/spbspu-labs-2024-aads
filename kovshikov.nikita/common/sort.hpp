#ifndef SORT_HPP
#define SORT_HPP
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include "random.hpp"

namespace kovshikov
{
  bool isDigit(std::string str);

  template< typename FwdIterator, typename Compare >
  void selectionSort(FwdIterator begin, FwdIterator end, Compare comp);

  template< typename ListIterator, typename Compare >
  void shellSort(ListIterator begin, ListIterator end, Compare comp);

  template< typename Iterator, typename Compare >
  void bubbleSort(Iterator begin, Iterator end, Compare comp);

  template< typename T, typename Compare >
  void sortDataStructures(std::ostream& out, int size, Compare comp);
}

bool kovshikov::isDigit(std::string str)
{
  size_t size = str.length();
  for(size_t i = 0; i < size; i++)
  {
    if(!std::isdigit(str[i]))
    {
      return false;
    }
  }
  return true;
}

template< typename FwdIterator, typename Compare >
void kovshikov::selectionSort(FwdIterator begin, FwdIterator end, Compare comp)
{
  while(begin != end)
  {
    FwdIterator extreme = begin;
    FwdIterator current = begin;
    while(current != end)
    {
      if(comp(*current, *extreme))
      {
        extreme = current;
      }
      current++;
    }
    std::swap(*extreme, *begin);
    begin++;
  }
}

template< typename ListIterator, typename Compare >
void kovshikov::shellSort(ListIterator begin, ListIterator end, Compare comp)
{
  int size = 0;
  ListIterator temp = begin;
  while(temp != end)
  {
    size += 1;
    temp++;
  }
  for(int interval = size / 2; interval > 0; interval /= 2)
  {
    for(int i = 0; i < interval; i++)
    {
      ListIterator current = std::next(begin, i);
      ListIterator next = std::next(current, interval);
      int indexNext = i + interval;
      while(indexNext < size)
      {
        int count = 1;
        ListIterator prev = std::prev(next, interval);
        int indexPrev = indexNext - interval;
        while(indexPrev >= 0)
        {
          if(comp(*next, *prev))
          {
            std::swap(*next, *prev);
            if(indexPrev - interval >= 0)
            {
              next = std::prev(next, interval);
              count += 1;
            }
          }
          if(indexPrev - interval >= 0)
          {
            prev = std::prev(prev, interval);
          }
          indexPrev -= interval;
        }
        if(indexNext + interval < size)
        {
          next = std::next(next, interval * count);
        }
        indexNext += interval;
      }
    }
  }
}

template< typename Iterator, typename Compare >
void kovshikov::bubbleSort(Iterator begin, Iterator end, Compare comp)
{
  bool isSort = false;
  bool firstIteration = true;
  while(isSort != false || firstIteration == true)
  {
    isSort = false;
    firstIteration = false;
    Iterator current = begin;
    Iterator prev = current;
    current++;
    while(current != end)
    {
      if(comp(*current, *prev))
      {
        isSort = true;
        std::swap(*current, *prev);
      }
      prev = current;
      current++;
    }
  }
}

template< typename T, typename Compare >
void kovshikov::sortDataStructures(std::ostream& out, int size, Compare comp)
{
  std::forward_list< T > fwdList;
  DoubleList< T > list;
  std::deque< T > deque;

  getRandom(list, fwdList, deque, size);

  DoubleList< T > listBubble;
  myCopy(list.begin(), list.end(), std::front_inserter(listBubble));
  std::deque< T > dequeShell;
  myCopy(deque.begin(), deque.end(), std::back_inserter(dequeShell));
  std::deque< T > dequeBubble;
  myCopy(deque.begin(), deque.end(), std::back_inserter(dequeBubble));

  printConteiner(fwdList, out);
  selectionSort(fwdList.begin(), fwdList.end(), comp);
  printConteiner(fwdList, out);
  selectionSort(deque.begin(), deque.end(), comp);
  printConteiner(deque, out);
  shellSort(list.begin(), list.end(), comp);
  printConteiner(list, out);
  shellSort(dequeShell.begin(), dequeShell.end(), comp);
  printConteiner(dequeShell, out);
  bubbleSort(listBubble.begin(), listBubble.end(), comp);
  printConteiner(listBubble, out);
  bubbleSort(dequeBubble.begin(), dequeBubble.end(), comp);
  printConteiner(dequeBubble, out);
}

#endif
