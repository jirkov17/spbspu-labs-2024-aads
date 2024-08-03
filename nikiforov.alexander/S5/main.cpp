#include <iostream>
#include <functional>
#include <fstream>
#include "commandsTraverse.hpp"

int main(int argc, char* argv[])
{
  if (argc != 3)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }

  nikiforov::AvlTree< long long , std::string > traversalTree;
  std::string strData;

  std::getline(input, strData);
  nikiforov::createTree(strData, traversalTree);

  using namespace std::placeholders;
  nikiforov::AvlTree< std::string, std::function < void(nikiforov::AvlTree< long long, std::string >&, std::ostream&) > > cmds;
  {
    cmds.emplace("ascending", nikiforov::lnrTraverse);
    cmds.emplace("descending", nikiforov::rnlTraverse);
    cmds.emplace("breadth", nikiforov::breadthTraverse);
  }

  try
  {
    std::string cmd = argv[1];
    cmds.at(cmd)(traversalTree, std::cout);
  }
  catch (const std::exception& e)
  {
    nikiforov::errorMessage(std::cerr);
    return 1;
  }
  return 0;
}
