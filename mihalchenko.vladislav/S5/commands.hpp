#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <string>
#include <AVLtree.hpp>

namespace mihalchenko
{
  struct Key_summ
  {
    void operator()(const std::pair<long long, std::string> &value);
    int sum_ = 0;
    std::string valueRes_;
  };

  using AVLtree = mihalchenko::AVLTree<long long, std::string, long long>;

  std::ostream &printEmptyAVLTree(std::ostream &out);
  std::ostream &printInvalidCommandMessage(std::ostream &out);
  std::ostream &printErrorMessage(std::ostream &out);

  void ascending(std::ostream &out, AVLtree &allTree);
  void descending(std::ostream &out, AVLtree &allTree);
  void breadth(std::ostream &out, AVLtree &allTree);

  using commandsTree = mihalchenko::AVLTree<std::string, std::function<void(std::ostream &, AVLtree &)>, long long>;
  void clearTree(AVLtree &avlTree, commandsTree &commands);
}

#endif
