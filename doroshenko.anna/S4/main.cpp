#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <functional>
#include "treeProcess.hpp"

int main(int argc, char* argv[])
{
  using namespace doroshenko;
  BST< std::string, BST< long long, std::string > > treeOfDicts;
  BST< std::string, std::function< void(BST< std::string, BST< long long, std::string > >& treeOfDicts) > > treeOfFuncs;
  treeOfFuncs.insert("print", print);
  treeOfFuncs.insert("complement", complement);
  treeOfFuncs.insert("intersect", intersect);
  treeOfFuncs.insert("union", unify);
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  else
  {
    std::ifstream input(argv[1]);
    if (!input)
    {
      std::cerr << "Wrong file\n";
      return 1;
    }
    else
    {
      inputTree(input, treeOfDicts);
    }
  }
  while (!std::cin.eof())
  {
    std::string function;
    std::cin >> function;

    auto funcIter = treeOfFuncs.find(function);
    if (funcIter != treeOfFuncs.end() && !function.empty())
    {
      funcIter->second(treeOfDicts);
    }
    else if (!function.empty())
    {
      warningInvCom(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
