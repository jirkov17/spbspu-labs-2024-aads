#include <iostream>
#include <utility>
#include "cutFunctions.hpp"
#include "outputFunctions.hpp"
#include <algorithm>

int main()
{
  using pairs = ponomarev::List< std::pair< std::string, ponomarev::List< unsigned long long > > >;
  pairs data;
  pairs::Iterator iterator;
  std::string line = "";
  size_t maxLenSeq = 0;

  while (std::getline(std::cin, line))
  {
    if (line.size() != 0)
    {
      std::string name = ponomarev::getName(line);
      std::pair< std::string, ponomarev::List< unsigned long long > > pair = { name, {} };
      data.pushBack(pair);
      iterator = data.begin();
      for (size_t i = 0; i < (data.getSize() - 1); i++)
      {
        iterator++;
      }
      size_t temp = 0;
      while (!line.empty())
      {
        unsigned long long num = ponomarev::getNumber(line);
        iterator->second.pushBack(num);
        temp++;
      }
      maxLenSeq = std::max(maxLenSeq, temp);
    }
  }
  if (!data.isEmpty())
  {
    iterator = data.begin();
    while (iterator != data.end())
    {
      std::cout << iterator->first;
      iterator++;
      std::cout << (iterator == data.end() ? '\n' : ' ');
    }
  }
  bool overflowCheck = false;
  ponomarev::List< unsigned long long > sums = ponomarev::outputNums< unsigned long long >(data, maxLenSeq, overflowCheck);
  if (overflowCheck)
  {
    std::cerr << "Error detected very very very big value";
    return 1;
  }
  ponomarev::outputSums< unsigned long long >(sums);
  return 0;
}
