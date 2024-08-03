#include <limits>
#include "list.hpp"
#include "functions.hpp"

int main()
{
  using namespace doroshenko;
  try
  {
    List< std::pair< std::string, List< size_t > > > list = listInput(std::cin);
    List< List < size_t > > lists;
    List< size_t > sums;
    namesOutput(list, std::cout);
    if (!list.isEmpty())
    {
      listFormation(list, lists);
      if (!lists.isEmpty())
      {
        listsOutput(std::cout, lists);
        sumsFormation(lists, sums);
      }
      sumsOutput(std::cout, sums);
    }
    else
    {
      std::cout << 0 << "\n";
    }
    return 0;
  }
  catch (std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
}
