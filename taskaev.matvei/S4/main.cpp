#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include <limits>
#include "BSTree.hpp"
#include "functions.hpp"
using namespace taskaev;

int main(int argc, char ** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error: argument of file failed!\n";
    return 1;
  }
  BSTree< std::string, BSTree< size_t, std::string > > tres;
  std::ifstream inputs(argv[1]);
  if (!inputs)
  {
    std::cerr << "Error: input\n";
    return 1;
  }
  createTree(inputs, tres);
  BSTree< std::string, std::function< void(BSTree< std::string, BSTree< size_t, std::string > >&) > > cmds;
  cmds.insert("print", print);
  cmds.insert("complement", complement);
  cmds.insert("intersect", intersect);
  cmds.insert("union", unions);
  std::string command = "";
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(tres);
    }
    catch (const std::out_of_range& e)
    {
      errorInvalid(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
