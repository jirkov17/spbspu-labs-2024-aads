#include <iostream>
#include <limits>
#include <utility>
#include <string>
#include "List.hpp"
#include "functionList.hpp"

int main()
{
  using namespace taskaev;
  List< std::pair< std::string, List< size_t > > > list;
  List< size_t > sums;
  try
  {
    inputList(std::cin, list);
    if (list.isEmpty())
    {
      std::cout << "0\n";
      return 0;
    }
    else
    {
      outputListName(list);
      outputList(list, sums);
      outputSum(sums);
    }
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  return 0;
}
