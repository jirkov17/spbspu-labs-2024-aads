#include <iostream>
#include <fstream>
#include <functional>
#include <AVLtree.hpp>
#include "commands.hpp"

using AVLtree = mihalchenko::AVLTree<long long, std::string, long long>;

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    mihalchenko::printErrorMessage(std::cout);
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input)
  {
    mihalchenko::printErrorMessage(std::cout);
    return 1;
  }
  AVLtree allTree;
  try
  {
    while (!input.eof())
    {
      long long key = 0;
      std::string value = "";
      if (input >> key >> value)
      {
        allTree.insert(std::make_pair(key, value));
      }
    }
  }
  catch (const std::exception &e)
  {
    mihalchenko::printErrorMessage(std::cout);
    allTree.clear();
    return 1;
  }
  if (allTree.empty())
  {
    mihalchenko::printEmptyAVLTree(std::cout);
    return 0;
  }
  mihalchenko::AVLTree<std::string, std::function<void(std::ostream &, AVLtree &)>, long long> commands;
  {
    commands.insert("ascending", mihalchenko::ascending);
    commands.insert("descending", mihalchenko::descending);
    commands.insert("breadth", mihalchenko::breadth);
  }
  std::string direction = argv[1];
  try
  {
    commands.at(direction)(std::cout, allTree);
  }
  catch (const std::out_of_range &)
  {
    mihalchenko::printInvalidCommandMessage(std::cout);
    clearTree(allTree, commands);
    return 1;
  }
  clearTree(allTree, commands);
  return 0;
}
