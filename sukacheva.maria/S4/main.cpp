#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <string>
#include "BST.hpp"
#include "Commands.hpp"
#include "ErrorMessage.hpp"

int main(int argc, char* argv[])
{
  using namespace sukacheva;
  if (argc != 2)
  {
    std::cerr << "< INVALID NUMBER OF ARGUMENTS >\n";
    return 1;
  }
  std::ifstream in(argv[1]);
  if (!in)
  {
    std::cerr << "< UNABLE TO READ FILE >\n";
    return 2;
  }
  treeOfTrees treeOfDicts;
  while (!in.eof())
  {
    std::string line = {};
    while (std::getline(in, line))
    {
      if (!line.empty())
      {
        inputTree(treeOfDicts, line);
      }
    }
    if (in.fail())
    {
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  BST< std::string, std::function < void(treeOfTrees&, std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands.insert("print", std::bind(printCommand, _1, _2, _3));
    commands.insert("complement", std::bind(comlement, _1, _2, _3));
    commands.insert("intersect", std::bind(intersect, _1, _2, _3));
    commands.insert("union", std::bind(unionCommand, _1, _2, _3));
  }
  std::string inputCommand = {};
  while (std::cin >> inputCommand)
  {
    try
    {
      commands.at(inputCommand)(treeOfDicts, std::cin, std::cout);
    }
    catch (const std::exception& e)
    {
      ErrorMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
