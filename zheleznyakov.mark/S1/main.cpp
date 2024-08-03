#include <iostream>
#include <string>
#include "list.hpp"
#include "task.hpp"

int main()
{
  zheleznyakov::List< std::pair< std::string, zheleznyakov::List< unsigned long long > > >pairs;
  size_t pairsIndex = 0;
  std::string input;
  while (std::cin >> input)
  {
    if (std::isalpha(input[0]))
    {
      pairs.pushBack({ input, {} });
      pairsIndex++;
    }
    else
    {
      pairs[pairsIndex - 1].second.pushBack(std::stoull(input));
    }
  }
  try
  {
    zheleznyakov::processTask(std::cout, pairs);
  }
  catch(const std::overflow_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
