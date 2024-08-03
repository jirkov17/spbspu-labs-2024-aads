#include <utility>
#include <limits>
#include "list.hpp"
#include "InpOutpProcessing.hpp"

int main()
{
  using namespace mihalchenko;

  size_t maxLenOfSecondList = 0;
  size_t CountSecondList = 0;
  size_t CountmixedList = 0;
  using mainList = mihalchenko::List<std::pair<std::string, mihalchenko::List<size_t>>>;
  using integerList = mihalchenko::List<size_t>;
  mainList mixedList;
  integerList tempIntList;
  std::string inputStr;
  bool flgNamed = false;
  while (std::cin >> inputStr)
  {
    if (!isdigit(inputStr[0]))
    {
      std::string str;
      str = inputStr;
      flgNamed = true;
      tempIntList.clear();
      if (maxLenOfSecondList < CountSecondList)
      {
        maxLenOfSecondList = CountSecondList;
      }
      CountSecondList = 0;
      mixedList.push_back(std::make_pair(str, tempIntList));
      CountmixedList++;
    }
    else
    {
      size_t wrem = 0;
      sscanf(inputStr.c_str(), "%zu", &wrem);
      if (!flgNamed)
      {
        std::cerr << "No correct input!";
        std::cout << wrem << '\n';
        std::cout << 0 << '\n';
        return 0;
      }
      mixedList[CountmixedList - 1].second.push_back(wrem);
      if (inputStr == std::to_string(wrem))
      {
        CountSecondList++;
      }
      else
      {
        std::cerr << "Input overflow!";
        return 1;
      }
    }
  }
  if (mixedList.getSize() == 0)
  {
    std::cout << 0 << '\n';
    return 0;
  }

  mihalchenko::printName(mixedList, mixedList.getSize(), maxLenOfSecondList);

  bool flgNewStr = false;
  size_t ullMax = std::numeric_limits<size_t>::max();
  for (size_t numericView = 0; numericView < maxLenOfSecondList; numericView++)
  {
    size_t summa = mihalchenko::printMixedList(mixedList, mixedList.getSize(), numericView, flgNewStr);
    if (summa == ullMax)
    {
      std::cerr << "Input overflow!";
      return 1;
    }
    else
    {
      tempIntList.push_back(summa);
    }
  }
  mihalchenko::printSumDigit(tempIntList, tempIntList.getSize());
  return 0;
}
