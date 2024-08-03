#include <iostream>
#include <functional>
#include <map>
#include "outputFunction.hpp"

int main(int argc, char ** argv)
{
  if (argc != 4)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  int size = std::atoi(argv[3]);
  if (size == 0)
  {
      std::cerr << "Error: wrong size parameter\n";
      return 1;
  }

  std::map< std::string, std::map < std::string, std::function< void(std::ostream &, int) > > > functions{};
  {
    using namespace std::placeholders;
    functions["ints"]["ascending"] = std::bind(redko::sortData< int, std::less< int > >, _1, _2, std::less< int >());
    functions["ints"]["descending"] = std::bind(redko::sortData< int, std::greater< int > >, _1, _2, std::greater< int >());
    functions["floats"]["ascending"] = std::bind(redko::sortData< double, std::less< double > >, _1, _2, std::less< double >());
    functions["floats"]["descending"] = std::bind(redko::sortData< double, std::greater< double > >, _1, _2, std::greater< double >());
  }

  try
  {
    functions.at(argv[2]).at(argv[1])(std::cout, size);
  }
  catch (const std::out_of_range &)
  {
    std::cerr << "Error: wrong parameter\n";
    return 1;
  }

  return 0;
}
