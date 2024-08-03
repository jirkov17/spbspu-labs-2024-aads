#include <iostream>
#include <string>
#include <functional>
#include <string>
#include <fstream>
#include <utility>
#include <limits>
#include <functional>
#include "tree.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace khoroshkin;
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 2;
  }

  Tree< std::string, Tree< long long, std::string > > TreeOfDataSets{};
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Cannot open file\n";
    return 2;
  }

  std::string line;
  while (getline(input, line))
  {
    size_t pos = 0;
    std::string name = getString(line, pos);
    khoroshkin::Tree< long long, std::string > datasets{};
    while (pos < line.length())
    {
      long long key = getKey(line, pos);
      std::string value = getString(line, pos);
      datasets.insert(key, value);
    }
    TreeOfDataSets.insert(name, datasets);
  }

  Tree< std::string, std::function< void(Tree< std::string, Tree< long long, std::string > > & Tree) > > TreeOfFuntions{};
  TreeOfFuntions.insert("print", print);
  TreeOfFuntions.insert("complement", complement);
  TreeOfFuntions.insert("intersect", intersect);
  TreeOfFuntions.insert("union", unite);

  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  while (!std::cin.eof())
  {
    std::string todo;
    std::cin >> todo;

    auto function = TreeOfFuntions.find(todo);
    if (function == TreeOfFuntions.end() && todo.length() > 0)
    {
      outInvalid(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    else if (todo.length() > 0)
    {
      (*function).second(TreeOfDataSets);
    }
  }

  return 0;
}
