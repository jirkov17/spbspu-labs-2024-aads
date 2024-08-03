#include <iostream>
#include "doublelist.hpp"
#include "IOProcess.hpp"

int main()
{
  using namespace kovshikov;
  listPair allPairs;
  bool isBigNumber = false;
  inputPairs(allPairs, isBigNumber);
  outputListName(allPairs);
  DoubleList< size_t > summaList;
  listOfList resultList;
  processInput(summaList, resultList, allPairs);
  outputLists(resultList);
  outputSumma(isBigNumber, summaList);
  if(isBigNumber == true)
  {
    std::cerr << "too many numbers were entered\n";
    return 1;
  }
  return 0;
}
