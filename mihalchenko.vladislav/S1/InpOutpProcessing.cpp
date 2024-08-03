#include "InpOutpProcessing.hpp"
#include <limits>

size_t mihalchenko::printName(mainList &mixedList, size_t mixedListSize, size_t maxLenOfSecondList)
{
  for (size_t i = 0; i < mixedListSize; i++)
  {
    std::cout << mixedList[i].first;
    if (i != mixedListSize - 1)
    {
      std::cout << " ";
    }
  }

  if (maxLenOfSecondList == 0)
  {
    std::cout << '\n';
    std::cout << 0;
    return 0;
  }
  std::cout << '\n';
  return 0;
}

size_t mihalchenko::printSumDigit(integerList &tempIntList, size_t tempIntListSize)
{
  for (size_t i = 0; i < tempIntListSize; i++)
  {
    std::cout << tempIntList[i];
    if (i != tempIntListSize - 1)
    {
      std::cout << " ";
    }
  }
  std::cout << '\n';
  return 0;
}

size_t mihalchenko::printMixedList(mainList &mixedList, size_t mixedListSize, size_t numericView, bool &flgNewStr)
{
  size_t summa = 0;
  flgNewStr = true;
  summa = 0;
  size_t ullMax = std::numeric_limits< size_t >::max();
  for (size_t i = 0; i < mixedListSize; i++)
  {
    if (mixedList[i].second.getSize() > numericView)
    {
      if (flgNewStr)
      {
        std::cout << mixedList[i].second[numericView];
        flgNewStr = false;
      }
      else
      {
        std::cout << " " << mixedList[i].second[numericView];
      }
      if (ullMax - mixedList[i].second[numericView] >= summa)
      {
        summa = summa + mixedList[i].second[numericView];
      }
      else
      {
        std::cout << '\n';
        std::cerr << "Input overflow!";
        return ullMax;
      }
    }
  }
  std::cout << '\n';
  return summa;
}
