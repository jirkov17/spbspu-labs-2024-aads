#include "commands.hpp"
#include <iostream>
#include <limits>
#include <stdexcept>

using AVLtree = mihalchenko::AVLTree<long long, std::string, long long>;

void mihalchenko::ascending(std::ostream &out, AVLtree &allTree)
{
  mihalchenko::Key_summ sum;
  sum = allTree.traverseLR<Key_summ>(sum);

  out << sum.sum_ << sum.valueRes_ << "\n";
}

void mihalchenko::descending(std::ostream &out, AVLtree &allTree)
{
  mihalchenko::Key_summ sum;
  sum = allTree.traverseRL<Key_summ>(sum);

  out << sum.sum_ << sum.valueRes_ << "\n";
}

void mihalchenko::breadth(std::ostream &out, AVLtree &allTree)
{
  mihalchenko::Key_summ sum;
  sum = allTree.traverseBreadth<Key_summ>(sum);

  out << sum.sum_ << sum.valueRes_ << "\n";
}

void mihalchenko::Key_summ::operator()(const std::pair<long long, std::string> &value)
{
  bool checkOverflow = (value.first > 0) && (sum_ > (std::numeric_limits<long long>::max() - value.first));
  if (checkOverflow)
  {
    throw std::out_of_range("Error: owerflow\n");
  }

  bool checkUnderflow = (value.first < 0) && (sum_ < (std::numeric_limits<long long>::min() - value.first));
  if (checkUnderflow)
  {
    throw std::out_of_range("Error: underflow\n");
  }

  sum_ += value.first;
  valueRes_ += (" " + value.second);
}

std::ostream &mihalchenko::printEmptyAVLTree(std::ostream &out)
{
  out << "<EMPTY>\n";
  return out;
}

std::ostream &mihalchenko::printInvalidCommandMessage(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream &mihalchenko::printErrorMessage(std::ostream &out)
{
  out << "<Exception opening/reading/closing file>\n";
  return out;
}

void mihalchenko::clearTree(AVLtree &avlTree, commandsTree &commands)
{
  avlTree.clear();
  commands.clear();
}
