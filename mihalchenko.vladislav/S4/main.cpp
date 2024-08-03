#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <utility>
#include <limits>
#include "AVLtree.hpp"
#include "commands.hpp"

int main(int argc, char *argv[])
{
  using namespace mihalchenko;
  if (argc != 2)
  {
    std::cerr << "Incorrect command line parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error opening the file\n";
    return 1;
  }
  std::string inputStr;
  using substitute = AVLTree< std::string, AVLTree< long long, std::string > >;
  substitute TreeAndLeaves{};
  while (getline(input, inputStr))
  {
    insertDataToTree(TreeAndLeaves, inputStr);
  }
  AVLTree< std::string, std::function< void(substitute & AVLTree) > > commands{};
  commands.insert("print", print);
  commands.insert("union", unionAVL);
  commands.insert("intersect", intersect);
  commands.insert("complement", complement);
  while (!std::cin.eof())
  {
    std::string inputCommand;
    std::cin >> inputCommand;
    if ((commands.find(inputCommand) == commands.end()) && (!inputCommand.empty()))
    {
      mihalchenko::printInvalidCommand(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    else if (!inputCommand.empty())
    {
      (*commands.find(inputCommand)).second(TreeAndLeaves);
    }
  }
  return 0;
}
