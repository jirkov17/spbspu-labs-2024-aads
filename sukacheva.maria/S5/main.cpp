#include <iostream>
#include <fstream>
#include <functional>
#include <limits>
#include <string>
#include "BST.hpp"
#include "DataProcessing.hpp"
#include "ErrorMessage.hpp"

int main(int argc, char* argv[])
{
  using namespace sukacheva;
  if (argc != 3)
  {
    std::cerr << "<INVALID NUMBER OF ARGUMENTS>\n";
    return 1;
  }
  std::ifstream in(argv[2]);
  if (!in)
  {
    std::cerr << "<UNABLE TO READ FILE>\n";
    return 2;
  }
  BinaryTree tree;
  std::string line = {};
  std::getline(in, line);
  if (!line.empty())
  {
    inputTree(tree, line);
  }
  if (in.fail())
  {
    in.clear();
    in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }

  BST< std::string, std::function < void(BinaryTree&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands.insert("ascending", std::bind(ascendingCommand, _1, _2));
    commands.insert("descending", std::bind(descendingCommand, _1, _2));
    commands.insert("breadth", std::bind(breadthCommand, _1, _2));
  }
  try
  {
    commands.at(argv[1])(tree, std::cout);
  }
  catch (const std::exception& e)
  {
    ErrorMessage(std::cerr);
    return 1;
  }
  return 0;
}
