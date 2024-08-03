#include <iostream>
#include <fstream>
#include <tree.hpp>
#include "input.hpp"
#include "commands.hpp"

int main(int argc, char * argv[])
{
  using namespace zheleznyakov;

  if (argc != 3)
  {
    std::cerr << "Wrong arguments count\n";
    return 2;
  }

  std::ifstream in(argv[2]);
  if (!in)
  {
    std::cerr << "Unable to read file\n";
    return 2;
  }

  data_t data;
  std::string line;
  std::getline(in, line);
  readData(line, data);

  if (data.empty())
  {
    outEmpty(std::cout);
    return 0;
  }

  Tree< std::string, std::function< void(std::ostream &, const data_t &) > > cmds;
  cmds["ascending"] = commands::ascending;
  cmds["descending"] = commands::descending;
  cmds["breadth"] = commands::breadth;
  std::string command = argv[1];

  try
  {
    cmds.at(command)(std::cout, data);
  }
  catch(const std::exception &)
  {
    outInvalidCommand(std::cerr);
    return 1;
  }

  return 0;
}
