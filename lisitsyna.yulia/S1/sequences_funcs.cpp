#include "sequences_funcs.hpp"
#include <iostream>

#include "except_sum.hpp"

sequences_t readSequences(size_t & maxLen, std::istream & in)
{
  List< std::pair< std::string, List< unsigned long long > > > sequences;
  maxLen = 0;
  while (!in.eof() && !in.fail())
  {
    std::string name, numbers;
    in >> name;
    if (name.empty())
    {
      continue;
    }
    std::getline(in, numbers);
    List< unsigned long long > list;
    if (numbers.empty())
    {
      sequences.push_back({ name, std::move(list) });
      continue;
    }
    size_t count = 0;
    std::string number;
    for (size_t i = 0; i < numbers.length(); ++i)
    {
      if (std::isdigit(numbers[i]))
      {
        number += numbers[i];
      }
      else if (!number.empty())
      {
        unsigned long long num = std::stoull(number);
        list.push_back(num);
        number.clear();
        ++count;
      }
    }
    if (!number.empty())
    {
      unsigned long long num = std::stoull(number);
      list.push_back(num);
      ++count;
    }
    maxLen = std::max(maxLen, count);
    sequences.push_back({ name, std::move(list) });
  }

  return sequences;
}

void outSequencesName(const sequences_t & sequences, std::ostream & out)
{
  bool first = true;
  for (const auto & seq: sequences)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      out << ' ';
    }
    out << seq.first;
  }
}

void outSequencesValues(const sequences_t & sequences, size_t maxLen, std::ostream & out)
{
  bool first = true;
  for (size_t i = 0; i < maxLen; ++i)
  {
    first = true;
    for (const auto & seq: sequences)
    {
      const auto & list = seq.second;
      auto it = list.begin();
      for (size_t j = 0; j < i && it != list.end(); ++j)
      {
        ++it;
      }
      if (it != list.end())
      {
        if (first)
        {
          first = false;
        }
        else
        {
          out << ' ';
        }
        out << *it;
      }
    }
    out << '\n';
    if (sequences.empty())
    {
      out << 0;
    }
  }
}

List< unsigned long long > sumSequencesValues(const sequences_t & sequences, size_t maxLen)
{
  List< unsigned long long > sums;
  for (size_t i = 0; i < maxLen; ++i)
  {
    sums.push_back(0);
    for (const auto & seq: sequences)
    {
      const auto & list = seq.second;
      auto it = list.begin();
      for (size_t j = 0; j < i && it != list.end(); ++j)
      {
        ++it;
      }
      if (it != list.end())
      {
        sums.back() = sum(sums.back(), *it);
      }
    }
  }
  return sums;
}

void outSequence(const List< unsigned long long > & sequence, std::ostream & out)
{
  bool first = true;
  for (auto value: sequence)
  {
    if (first)
    {
      first = false;
    }
    else
    {
      out << ' ';
    }
    out << value;
  }
}

