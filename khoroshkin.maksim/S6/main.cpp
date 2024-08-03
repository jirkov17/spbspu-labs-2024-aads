#include <iostream>
#include <string>
#include <iomanip>
#include <functional>
#include "sort.hpp"
#include "tree.hpp"
#include "inputProcessing.hpp"

int main(int argc, char * argv[])
{
  using namespace khoroshkin;
  srand(time(0));

  if (argc != 4)
  {
    std::cerr << "Error: wrong input!\n";
    return 1;
  }
  if (std::isdigit(std::string(argv[3])[0]) && std::stoull(argv[3]) < 1)
  {
    std::cerr << "Error: size must be >0\n";
    return 1;
  }

  Tree< std::string, std::function< void (std::ostream & stream, size_t size) > > insideBranchingLess;
  Tree< std::string, std::function< void (std::ostream & stream, size_t size) > > insideBranchingGreater;
  Tree< std::string, Tree< std::string, std::function< void (std::ostream & stream, size_t size) > > > sortTree;
  {
    using namespace std::placeholders;
    insideBranchingLess.insert("ints", std::bind(sortData< int, std::less< int > >, _1, _2, std::less< int >{}));
    insideBranchingLess.insert("floats", std::bind(sortData< double, std::less< double > >, _1, _2, std::less< double >{}));

    insideBranchingGreater.insert("ints", std::bind(sortData< int, std::greater< int > >, _1, _2, std::greater< int >{}));
    insideBranchingGreater.insert("floats", std::bind(sortData< double, std::greater< double > >, _1, _2, std::greater< double >{}));

    sortTree.insert("ascending", insideBranchingLess);
    sortTree.insert("descending", insideBranchingGreater);
  }

  auto func = sortTree.find(std::string(argv[1]));
  if (func == sortTree.end())
  {
    std::cerr << "Error: wrong input\n";
    return 1;
  }
  auto inFunc = (*func).second.find(std::string(argv[2]));
  if (inFunc == (*func).second.end())
  {
    std::cerr << "Error: wrong input\n";
    return 1;
  }
  (*inFunc).second(std::cout, std::stoull(argv[3]));

  return 0;
}
