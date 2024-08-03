#ifndef TASK_HPP
#define TASK_HPP
#include <iostream>
#include <string>
#include <limits>
#include "list.hpp"

namespace zheleznyakov
{
  using list_type = std::pair< std::string, List< unsigned long long > >;
  void processTask(std::ostream&, List< list_type >&);
  void processTitles(std::ostream&, List< list_type >&);
  void processSequences(std::ostream&, List< list_type >&);
  size_t findMaxSequenceLength(List< list_type >&);
}

void zheleznyakov::processTask(std::ostream& out, List< list_type >& pairs)
{
  processTitles(out, pairs);
  processSequences(out, pairs);
}

void zheleznyakov::processTitles(std::ostream& out, List< list_type >& pairs)
{
  using list_type = list_type;
  List< list_type >::Iterator iter(pairs.begin());
  while (iter != pairs.end())
  {
    out << (*iter).first;
    iter++;
    if (iter == pairs.end()) out << "\n";
    else out << " ";
  }
}

void zheleznyakov::processSequences(std::ostream& out, List< list_type >& pairs)
{
  using list_type = list_type;
  const size_t maxSequenceLength = findMaxSequenceLength(pairs);
  zheleznyakov::List< unsigned long long > sums;
  unsigned long long currentSum = 0;
  bool overflowFlag = false;
  for (size_t i = 0; i < maxSequenceLength; i++)
  {
    currentSum = 0;
    for (List< list_type >::Iterator iter(pairs.begin()); iter != pairs.end(); iter++)
    {
      if ((*iter).second.getSize() > i)
      {
        if (currentSum != 0)
        {
          out << ' ';
        }
        out << (*iter).second[i];
        if (currentSum > (std::numeric_limits< unsigned long long >::max() - (*iter).second[i]))
        {
          overflowFlag = true;
        }
        else
        {
          currentSum += (*iter).second[i];
        }
      }
    }
    sums.pushBack(currentSum);
    out << '\n';
  }
  if (overflowFlag)
  {
    throw std::overflow_error("Got overflow while calculating sums");
  }
  if (sums.getSize() == 0)
  {
    out << 0 << '\n';
  }
  else
  {
    List< unsigned long long >::Iterator iter(sums.begin());
    while (iter != sums.end())
    {
      out << (*iter);
      iter++;
      if (iter == sums.end())
      {
        out << "\n";
      }
      else
      {
        out << " ";
      }
    }
  }
}

size_t zheleznyakov::findMaxSequenceLength(List< list_type > &pairs)
{
  size_t maxSequenceLength = 0;
  for (List< list_type >::Iterator iter(pairs.begin()); iter != pairs.end(); iter++)
  {
    maxSequenceLength = std::max(maxSequenceLength, (*iter).second.getSize());
  }
  return maxSequenceLength;
}
#endif
