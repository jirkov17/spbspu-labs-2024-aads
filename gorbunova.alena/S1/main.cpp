#include <limits>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "func.hpp"

int main()
{
  gorbunova::List< std::pair< std::string, std::vector< unsigned long long > > > sequences;
  gorbunova::List< unsigned long long > sums;
  std::string input;
  std::string tempWord;
  bool containsEmptySequence = false;
  while (std::getline(std::cin, input))
  {
    if (input.empty())
    {
      std::cout << 0 << std::endl;
      return 0;
    }
    auto words = gorbunova::splitString(input);
    tempWord = words[0];
    std::vector< unsigned long long > numbers;
    for (size_t i = 1; i < words.size(); ++i)
    {
      numbers.push_back(std::stoull(words[i]));
    }
    sequences.push_back(std::make_pair(tempWord, numbers));
    if (numbers.empty())
    {
      containsEmptySequence = true;
    }
  }
  if (containsEmptySequence && sequences.getSize() == 1)
  {
    std::cout << tempWord << "\n"
              << 0 << "\n";
    return 0;
  }
  size_t max_size = 0;
  for (auto it = sequences.begin(); it != sequences.end(); ++it)
  {
    max_size = std::max(max_size, (*it).second.size());
  }
  printSequences(sequences, max_size);
  try
  {
    calculateSums(sequences, sums, max_size);
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  printSums(sums);
  return 0;
}
