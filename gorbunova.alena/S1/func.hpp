#include <limits>
#include "list.hpp"

namespace gorbunova
{
  void printSums(const gorbunova::List< unsigned long long > &sums);
  void printSequences(const gorbunova::List< std::pair< std::string, std::vector< unsigned long long > > > &sequences,
    size_t max_size);
  std::vector< std::string > splitString(const std::string &input);
  void calculateSums(gorbunova::List< std::pair< std::string, std::vector< unsigned long long > > > &sequences,
    gorbunova::List< unsigned long long > &sums, size_t max_size);
}
void gorbunova::printSums(const gorbunova::List< unsigned long long > &sums)
{
  for (auto it = sums.begin(); it != sums.end(); ++it)
  {
    std::cout << (*it);
    auto nextIt = it;
    ++nextIt;
    if (nextIt != sums.end())
    {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
}

void gorbunova::printSequences(const gorbunova::List< std::pair< std::string, std::vector< unsigned long long > > > &sequences,
  size_t max_size)
{
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    std::cout << (*it).first;
    auto nextIt = it;
    ++nextIt;
    if (nextIt != sequences.end())
    {
      std::cout << " ";
    }
  }
  std::cout << std::endl;
  for (size_t i = 0; i < max_size; ++i)
  {
    bool firstElement = true;
    for (const auto &pair : sequences)
    {
      const auto &sequence = pair.second;
      if (i < sequence.size())
      {
        if (!firstElement)
        {
          std::cout << " ";
        }
        std::cout << sequence[i];
        firstElement = false;
      }
    }
    std::cout << std::endl;
  }
}

std::vector< std::string > gorbunova::splitString(const std::string &input)
{
  std::vector< std::string > result;
  std::string word;
  for (const char &c : input)
  {
    if (c == ' ')
    {
      if (!word.empty())
      {
        result.push_back(word);
        word.clear();
      }
    }
    else
    {
      word += c;
    }
  }
  if (!word.empty())
  {
    result.push_back(word);
  }
  return result;
}

void gorbunova::calculateSums(gorbunova::List< std::pair< std::string, std::vector< unsigned long long > > > &sequences,
  gorbunova::List< unsigned long long > &sums, size_t max_size)
{
  for (size_t i = 0; i < max_size; ++i)
  {
    unsigned long long sum = 0;
    for (auto it = sequences.begin(); it != sequences.end(); ++it)
    {
      if (i < (*it).second.size())
      {
        if (sum > std::numeric_limits< unsigned long long >::max() - (*it).second[i])
        {
          throw std::overflow_error("Overflow");
        }
        sum += (*it).second[i];
      }
    }
    sums.push_back(sum);
  }
}
