#include <iostream>
#include <string>
#include <exception>
#include "List.hpp"
#include "DataProcessing.hpp"

int main()
{
  using namespace sukacheva;
  try {
    List< std::pair< std::string, List< size_t > > > newList = listInput(std::cin);
    if (maxListSize(newList) == 0)
    {
      if (!newList.empty())
      {
        printNameList(newList);
      }
      std::cout << "0\n";
    }
    else
    {
      printNameList(newList);
      bool overflowFlag = false;
      List< size_t > sumOfArgs;
      printArgs(newList, overflowFlag, sumOfArgs);
      if (!overflowFlag)
      {
        getSumsList(sumOfArgs);
      }
    }
  }
  catch (const std::exception& e) {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
