#include <iostream>
#include <limits>
#include <fstream>
#include "tree.hpp"
#include "IOProcessing.hpp"
#include "commands.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;

  if (argc != 2)
  {
    std::cerr << "Wrong amount of launch parameters\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file)
  {
    std::cerr << "Error while opening file\n";
    return 1;
  }

  Tree< std::string, Data > datasets;
  while (!file.eof())
  {
    inputDatasets(file, datasets);
    if (file.fail() && !file.eof())
    {
      file.clear();
      file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  Tree< std::string, commands::Command > commands;

  commands["print"] = commands::print;
  commands["complement"] = commands::complement;
  commands["intersect"] = commands::intersect;
  commands["union"] = commands::unite;

  std::string command = "";
  while(std::cin >> command)
  {
    try
    {
      commands.at(command)(std::cin, std::cout, datasets);
    }
    catch (const std::out_of_range& e)
    {
      sendInvalidCommand(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
