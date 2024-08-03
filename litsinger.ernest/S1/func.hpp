#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <string>
#include <iostream>
#include <limits>
#include "list.hpp"

namespace litsinger
{
  using this_t = List< std::pair< std::string, List< size_t > > >;

  size_t maxSize(this_t& list)
  {
    size_t size = 0;
    size_t maxxSize = 0;
    this_t::Iterator iterator = list.begin();
    while (iterator != this_t::ConstIterator())
    {
      size = iterator->second.getSize();
      maxxSize = size > maxxSize ? size : maxxSize;
      iterator++;
    }
    return maxxSize;
  }

  this_t listInput(std::istream& input)
  {
    std::string inputString = "";
    this_t inputList;
    unsigned long long readNumber = 0;
    const size_t maximum = std::numeric_limits< size_t >::max();
    while (input >> inputString)
    {
      if (std::isalpha(inputString[0]))
      {
        inputList.pushBack({ inputString, List< size_t >() });
      }
      else
      {
        readNumber = std::stoull(inputString);
        if (readNumber > maximum)
        {
          throw std::overflow_error("overflow error");
        }
        else
        {
          inputList.back().second.pushBack(readNumber);
        }
      }
    }
    return inputList;
  }

  void namesOutput(this_t& list, std::ostream& output)
  {
    this_t::Iterator iterator = list.begin();
    bool hasNumbers = false;

    if (!list.isEmpty())
    {
      while (iterator != list.end())
      {
        if (iterator != list.begin())
        {
          output << " ";
        }
        output << iterator->first;
        if (!iterator->second.isEmpty())
        {
          hasNumbers = true;
        }
        iterator++;
      }
      output << "\n";
    }

    if (!hasNumbers)
    {
      output << "0\n";
    }
  }

  void listFormation(this_t& mainList, List< List < size_t > >& lists)
  {
    this_t::Iterator iterator;
    size_t maxxSize = maxSize(mainList);
    List< size_t >::Iterator localIterator = List< size_t >::ConstIterator();
    List< size_t > curList;
    for (size_t index = 0; index < maxxSize; index++)
    {
      iterator = mainList.begin();
      while (iterator != mainList.end())
      {
        if (iterator->second[index] != nullptr)
        {
          localIterator = List< size_t >::ConstIterator(iterator->second[index]);
          curList.pushBack(*localIterator);
        }
        iterator++;
      }
      lists.pushBack(curList);
      curList.clear();
    }
  }

  void Sum(List< size_t >& list, List< size_t >& sums)
  {
    List< size_t >::Iterator iterator = list.begin();
    const size_t maximum = std::numeric_limits< size_t >::max();
    bool overflowError = false;
    size_t sum = 0;
    while (iterator != list.end())
    {
      if (iterator != List< size_t >::ConstIterator())
      {
        if (maximum - sum < *iterator)
        {
          overflowError = true;
        }
        else
        {
          sum = sum + *iterator;
        }
      }
      iterator++;
    }
    if (!overflowError)
    {
      sums.pushBack(sum);
    }
    else
    {
      throw std::overflow_error("overflow error");
    }
  }

  void sumsFormation(List< List < size_t > >& lists, List< size_t >& sums)
  {
    List< List< size_t > >::Iterator iterator = lists.begin();
    while (iterator != lists.end())
    {
      Sum(*iterator, sums);
      iterator++;
    }
  }

  void printList(std::ostream& output, List< size_t > list)
  {
    List< size_t >::Iterator iterator = list.begin();
    size_t size = list.getSize();
    for (size_t i = 0; i < size; i++)
    {
      output << *iterator;
      if (i != size - 1)
      {
        output << " ";
      }
      iterator++;
    }
  }

  void listsOutput(std::ostream& output, List< List< size_t > >& lists)
  {
    List< List< size_t > >::Iterator iterator = lists.begin();
    while (iterator != lists.end())
    {
      printList(output, *iterator);
      output << "\n";
      iterator++;
    }
  }

  void sumsOutput(std::ostream& output, List< size_t >& sums)
  {
    List< size_t >::Iterator iteratorForSums = sums.begin();
    if (sums.isEmpty())
    {
      output << 0;
    }
    else
    {
      while (iteratorForSums != sums.end())
      {
        if (iteratorForSums != List< size_t >::ConstIterator())
        {
          if (iteratorForSums != sums.begin())
          {
            output << " ";
          }
          output << *iteratorForSums;
        }
        iteratorForSums++;
      }
    }
    output << "\n";
  }
}

#endif
