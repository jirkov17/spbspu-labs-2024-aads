#include <functional>
#include <map>
#include <iostream>
#include "distributionFunctions.hpp"
#include "outputErrorFunctions.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    ponomarev::printInvalidParameters(std::cout);
    return 2;
  }

  int size = std::atoi(argv[3]);
  if (size == 0)
  {
      ponomarev::pringWrongSize(std::cout);
      return 1;
  }

  std::map< std::string, std::map < std::string, std::function< void(std::ostream &, int) > > > commands;
  {
    using namespace std::placeholders;
    commands["ints"]["ascending"] = std::bind(ponomarev::makeSort< int, std::less< int > >, _1, _2, std::less< int >());
    commands["ints"]["descending"] = std::bind(ponomarev::makeSort< int, std::greater< int > >, _1, _2, std::greater< int >());
    commands["floats"]["ascending"] = std::bind(ponomarev::makeSort< double, std::less< double > >, _1, _2, std::less< double >());
    commands["floats"]["descending"] = std::bind(ponomarev::makeSort< double, std::greater< double > >, _1, _2, std::greater< double >());
  }

  try
  {
    commands.at(argv[2]).at(argv[1])(std::cout, size);
  }
  catch (const std::out_of_range &)
  {
    ponomarev::printInvalidParameters(std::cout);
    return 1;
  }

  return 0;
}
