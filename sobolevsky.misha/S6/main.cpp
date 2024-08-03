#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include "shakerSort.hpp"
#include "mergeSort.hpp"
#include "sortsAgregatorContainerIOandErrors.hpp"
#include <tree.hpp>

using cmdDeclaration = sobolevsky::AVLtree< std::string, std::function< void(std::ostream &, size_t) >, bool >;

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "missed some argc\n";
    return 1;
  }

  std::string first = argv[1];
  std::string second = argv[2];

  size_t size;
  try
  {
    size = std::stoull(argv[3]);
  }
  catch(const std::invalid_argument &e)
  {
    sobolevsky::errorOutput(std::cerr);
    return 1;
  }

  if (size < 1)
  {
    sobolevsky::errorOutput(std::cerr);
    return 1;
  }

  sobolevsky::AVLtree< std::string, cmdDeclaration, bool >  cmds;
  using namespace std::placeholders;
  cmds["ascending"]["ints"] = std::bind(sobolevsky::sortsAgregator< int, std::less< int > >, _1, _2, std::less< int >{});
  cmds["descending"]["ints"] = std::bind(sobolevsky::sortsAgregator< int, std::greater< int > >, _1, _2, std::greater< int >{});
  cmds["ascending"]["floats"] = std::bind(sobolevsky::sortsAgregator< double, std::less< double > >, _1, _2, std::less< double >{});
  cmds["descending"]["floats"] = std::bind(sobolevsky::sortsAgregator< double, std::greater< double > >, _1, _2, std::greater< double >{});
  try
  {
    cmds.at(first).at(second)(std::cout, size);
  }
  catch(const std::exception & e)
  {
    sobolevsky::errorOutput(std::cerr);
    for (sobolevsky::AVLtree< std::string, cmdDeclaration, bool >::Iterator iter = cmds.begin(); iter != cmds.end(); iter++)
    {
      iter->second.clear();
    }
    cmds.clear();
    return 1;
  }
  for (sobolevsky::AVLtree< std::string, cmdDeclaration, bool >::Iterator iter = cmds.begin(); iter != cmds.end(); iter++)
  {
    iter->second.clear();
  }
  cmds.clear();
  return 0;
}
