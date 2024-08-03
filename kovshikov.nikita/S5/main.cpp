#include <fstream>
#include <iostream>
#include <string>
#include "BinarySearchTree.hpp"
#include "process.hpp"

int main(int argc, char ** argv)
{
  if(argc != 3)
  {
    std::cerr << "<NO SPECIFIED FILE>" << "\n";
    return 1;
  }

  using namespace kovshikov;
  Tree< int, std::string > tree;
  std::fstream file(argv[2]);

  Tree< std::string, std::function< void(Tree< int, std::string >&) > > commands;
  commands.insert("ascending", getAscending);
  commands.insert("descending", getDescending);
  commands.insert("breadth", getBreadth);

  try
  {
    readData(file, tree);
    commands.at(argv[1])(tree);
  }
  catch(const std::exception& error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
}
