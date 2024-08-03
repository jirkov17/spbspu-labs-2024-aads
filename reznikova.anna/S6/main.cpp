#include <iostream>
#include <map>
#include <functional>
#include "Sort.hpp"
#include "InputProcessing.hpp"

int main(int argc, char ** argv)
{
  using namespace reznikova;
  if (argc != 4)
  {
    wrongInputOutput(std::cerr);
    return 1;
  }
  std::string comparator = argv[1];
  if (!(comparator == "ascending" or comparator == "descending"))
  {
    wrongInputOutput(std::cerr);
    return 1;
  }
  std::string type = argv[2];
  if (!(type == "ints" or type == "floats"))
  {
    wrongInputOutput(std::cerr);
    return 1;
  }
  size_t size;
  try
  {
    size = std::stoll(argv[3]);
  }
  catch (std::exception &)
  {
    wrongInputOutput(std::cerr);
    return 1;
  }
  if (size == 0)
  {
    wrongInputOutput(std::cerr);
    return 1;
  }

  std::map< std::string, std::map< std::string, std::function<void(std::ostream &, std::string, size_t) > > > sorts{};
  {
    using namespace std::placeholders;
    sorts["ascending"]["ints"] = std::bind(sortData< int, std::less< int > >, _1, _2, _3, std::less< int >{});
    sorts["descending"]["ints"] = std::bind(sortData< int, std::greater< int > >, _1, _2, _3, std::greater< int >{});
    sorts["ascending"]["floats"] = std::bind(sortData< float, std::less< float > >, _1, _2, _3, std::less< float >{});
    sorts["descending"]["floats"] = std::bind(sortData< float, std::greater< float > >, _1, _2, _3, std::greater< float >{});
  }
  try
  {
    sorts.at(comparator).at(type)(std::cout, type, size);
  }
  catch(const std::exception &)
  {
    sortErrorOutput(std::cerr);
    return 1;
  }
  return 0;
}
