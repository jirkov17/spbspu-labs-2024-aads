#include <fstream>
#include "avlTree.hpp"
#include "execCommands.hpp"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: Wrong parameters amount!\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: Can't open a file!\n";
    return 2;
  }

  using base_t = psarev::avlTree< int, std::string >;
  psarev::avlTree< std::string, base_t > dataSets;

  psarev::fillTree(input, dataSets);

  psarev::avlTree< std::string, std::function< void(psarev::avlTree< std::string, base_t >&) > > taskCmds;
  taskCmds.insert({ "print", psarev::print });
  taskCmds.insert({ "complement", psarev::complement });
  taskCmds.insert({ "intersect", psarev::intersect });
  taskCmds.insert({ "union", psarev::unio });

  while (!std::cin.eof())
  {
    std::string cmd;
    std::cin >> cmd;

    auto curCmd = taskCmds.find(cmd);
    if (curCmd == taskCmds.end() && cmd.length() > 0)
    {
      psarev::outInvCommand(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    else if (cmd.length() > 0)
    {
      (*curCmd).second(dataSets);
    }
  }

  return 0;
}
