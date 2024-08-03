#include <iostream>
#include <string>
#include "MaineArray.hpp"
#include "AdditionalFunctions.hpp"

int main()
{
  using namespace kaseev;
  List< kaseev::ULL_ListPair > arr;
  std::string line;
  bool marker = false;
  while (std::getline(std::cin, line) && !line.empty())
  {
    readList(line, arr, marker);
  }

  printListNames(arr);
  List< IntListPair > sum = calculateSumList(arr);
  if (marker)
  {
    std::cerr << "overflow\n";
    return 1;
  }
  sumNumbersInArray(sum, marker);
  return 0;
}
