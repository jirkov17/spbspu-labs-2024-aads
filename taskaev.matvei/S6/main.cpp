#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <utility>
#include "sortFunctions.hpp"
#include "workSort.hpp"

int main(int argc, char **argv)
{
  using namespace taskaev;
  if (argc != 4)
  {
    std::cerr << "Error: arguments!\n";
    return 1;
  }
  size_t size = 0;
  try
  {
    size = std::stoll(argv[3]);
  }
  catch(...)
  {
    std::cerr << "Error: invalid argument.\n";
    return 1;
  }
  if (size == 0)
  {
    std::cerr << "Error: size zero!\n";
    return 1;
  }
  std::map< std::string, std::map< std::string, std::function< void(std::ostream&, std::string, size_t) > > > cmds{};
  {
    using namespace std::placeholders;
    cmds["ascending"]["ints"] = std::bind(workSortings< int, std::less< int > >, _1, _2, _3, std::less< int >{});
    cmds["ascending"]["floats"] = std::bind(workSortings< float, std::less< float > >, _1, _2, _3, std::less< float >{});
    cmds["descending"]["ints"] = std::bind(workSortings< int, std::greater< int > >, _1, _2, _3, std::greater< int >{});
    cmds["descending"]["floats"] = std::bind(workSortings< float, std::greater< float > >, _1, _2, _3, std::greater< float >{});
  }
  try
  {
    cmds.at(argv[1]).at(argv[2])(std::cout, argv[2], size);
  }
  catch(const std::exception&)
  {
    std::cerr << "ERROR: invalid work programm!\n";
    return 1;
  }
  return 0;
}
