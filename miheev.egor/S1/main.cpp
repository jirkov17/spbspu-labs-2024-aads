#include <iostream>
#include <utility>
#include <string>
#include "list.hpp"
#include "IOProcessing.hpp"

int main()
{
  using namespace miheev;

  SI_pair* pairs = nullptr;
  size_t pairsSize = 0;
  size_t unusedIndex = 0;

  while (!std::cin.eof())
  {
    if (unusedIndex >= pairsSize)
    {
      std::pair< SI_pair*, size_t > expanded = expandArr(pairs, pairsSize);
      SI_pair* temp = pairs;
      pairs = expanded.first;
      if (temp)
      {
        delete[] temp;
      }
      pairsSize = expanded.second;
    }

    SI_pair pair = getSIPair(std::cin);
    if (pair.first != "")
    {
      pairs[unusedIndex++] = pair;
    }
  }

  if (unusedIndex <= 0)
  {
    delete[] pairs;
    std::cout << "0\n";
    return 0;
  }

  for (size_t i = 0; i < unusedIndex; i++)
  {
    std::cout << pairs[i].first;
    if (i < unusedIndex - 1)
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';

  size_t maxSize = calcMaxListSize(pairs, unusedIndex);

  if (maxSize <= 0)
  {
    std::cout << "0\n";
    delete[] pairs;
    return 0;
  }

  size_t* sumArr = new size_t[maxSize]{};
  bool isOverflow = calcSumsArr(pairs, unusedIndex, sumArr);
  delete[] pairs;

  try
  {
    printSums(sumArr, maxSize, isOverflow);
  }
  catch(const std::runtime_error& err)
  {
    std::cerr << err.what();
    delete[] sumArr;
    return 1;
  }
  delete[] sumArr;

  return 0;
}
