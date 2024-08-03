#include <iostream>
#include <string>
#include <fstream>
#include <tree.hpp>
#include <commands.hpp>
#include "traverseFuncs.hpp"

int main(int argc, char * argv[])
{
  using namespace khoroshkin;
  if (argc != 3)
  {
    std::cerr << "Error: wrong input\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: wrong filename\n";
    return 2;
  }

  Tree< int, std::string > inputTree;
  std::string inputLine;
  getline(input, inputLine);
  size_t pos = 0;
  while (pos < inputLine.length())
  {
    try
    {
      int key = getKey(inputLine, pos);
      std::string value = getString(inputLine, pos);
      inputTree.insert(key, value);
    }
    catch(const std::out_of_range & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  Tree< std::string, std::function< void(const Tree< int, std::string > & data, std::ostream & out) > > treeOfType;
  treeOfType.insert("ascending", ascendingTraverse);
  treeOfType.insert("descending", descendingTraverse);
  treeOfType.insert("breadth", breadthTraverse);

  auto type = treeOfType.find(argv[1]);
  if (type == treeOfType.end())
  {
    outMessage(std::cerr, "Error: unexpected args\n");
    return 1;
  }
  else if (inputTree.isEmpty())
  {
    outMessage(std::cout, "<EMPTY>\n");
    return 0;
  }
  else if (type != treeOfType.end())
  {
    try
    {
      (*type).second(inputTree, std::cout);
    }
    catch(const std::exception & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }
  }

  return 0;
}
