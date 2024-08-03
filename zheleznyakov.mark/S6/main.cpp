#include <iostream>
#include <functional>
#include <map>
#include "sorts.hpp"
#include "random.hpp"

int main(int argc, char *argv[])
{
  srand(time(0));

  using namespace zheleznyakov;

  if (argc != 4)
  {
    errors::wrongArgsCount(std::cerr);
    return 2;
  }

  std::string order = argv[1];
  if (order != "ascending" && order != "descending")
  {
    errors::wrongSortOrder(std::cerr);
    return 1;
  }

  std::string dataType = argv[2];
  if (dataType != "ints" && dataType != "floats")
  {
    errors::wrongDataType(std::cerr);
    return 1;
  }

  int count = std::atoi(argv[3]);
  if (count <= 0)
  {
    errors::wrongSize(std::cerr);
    return 1;
  }

  std::map< std::string, std::map< std::string, std::function<void(std::ostream &, size_t) > > > executors;

  {
    using namespace std::placeholders;
    executors["ascending"]["ints"] = std::bind(executeSorts< int, std::less< int > >, _1, _2, std::less< int >{});
    executors["descending"]["ints"] = std::bind(executeSorts< int, std::greater< int > >, _1, _2, std::greater< int >{});
    executors["ascending"]["floats"] = std::bind(executeSorts< float, std::less< float > >, _1, _2, std::less< float >{});
    executors["descending"]["floats"] = std::bind(executeSorts< float, std::greater< float > >, _1, _2, std::greater< float >{});
  }

  try
  {
    executors.at(order).at(dataType)(std::cout, count);
  }
  catch(const std::exception&)
  {
    errors::outExecution(std::cerr);
    return 2;
  }

  return 0;
}
