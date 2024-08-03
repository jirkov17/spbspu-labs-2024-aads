#include <iostream>
#include <string>
#include <functional>
#include <map>
#include "funcsSort.hpp"

int main(int argc, char* argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::string firstParam = argv[1];
  std::string secondParam = argv[2];

  size_t size = 0;
  try
  {
    size = std::stoull(argv[3]);
  }
  catch (const std::invalid_argument& e)
  {
    nikiforov::errorMessages(std::cout);
    return 1;
  }

  if (size < 1)
  {
    nikiforov::errorMessages(std::cerr);
    return 1;
  }

  std::map< std::string, std::map< std::string, std::function< void(std::ostream&, size_t) > > > cmds;
  using namespace std::placeholders;
  cmds["ascending"]["ints"] = std::bind(nikiforov::makeSorted< int, std::less< int > >, _1, _2, std::less< int >());
  cmds["descending"]["ints"] = std::bind(nikiforov::makeSorted< int, std::greater< int > >, _1, _2, std::greater< int >());
  cmds["ascending"]["floats"] = std::bind(nikiforov::makeSorted< double, std::less< double > >, _1, _2, std::less< double >());
  cmds["descending"]["floats"] = std::bind(nikiforov::makeSorted< double, std::greater< double > >, _1, _2, std::greater< double >());

  try
  {
    cmds.at(firstParam).at(secondParam)(std::cout, size);
  }
  catch (const std::exception&)
  {
    nikiforov::errorMessages(std::cerr);
    return 1;
  }
  return 0;
}
