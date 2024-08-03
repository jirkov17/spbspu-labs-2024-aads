#include "commands.hpp"
#include <string>
#include <iostream>
#include <cctype>
#include <functional>
#include <utility>

std::string mihalchenko::resiveString(std::string &inputStr, size_t &pos, bool flag)
{
  std::string result = "";
  while (pos < inputStr.length() && inputStr[pos] != ' ')
  {
    if ((flag) || ((!flag) && std::isdigit(inputStr[pos])))
    {
      result += inputStr[pos++];
    }
    else if (!flag)
    {
      break;
    }
  }
  pos++;
  return result;
}

void mihalchenko::printInvalidCommand(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void mihalchenko::printEmptyMessage(std::ostream &out)
{
  out << "<EMPTY>\n";
}

void mihalchenko::print(typeParam &AVLTree)
{
  std::string name;
  std::cin >> name;
  auto iterList = AVLTree.find(name);
  if (iterList == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  else if ((*iterList).second.empty())
  {
    printEmptyMessage(std::cout);
    return;
  }

  std::cout << (*iterList).first << " ";
  for (auto it = (*iterList).second.begin(); it != (*iterList).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    if ((++it) == (*iterList).second.end())
    {
      std::cout << "\n";
    }
    else
    {
      std::cout << ' ';
    }
    it--;
  }
}

void mihalchenko::complement(typeParam &AVLTree)
{
  std::string nameNewGlossary, nameOneGlossary, nameTwoGlossary;
  std::cin >> nameNewGlossary >> nameOneGlossary >> nameTwoGlossary;

  if (AVLTree.find(nameOneGlossary) == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree< long long, std::string > compTree{};
  for (auto it = (*AVLTree.find(nameOneGlossary)).second.begin(); it != (*AVLTree.find(nameOneGlossary)).second.end(); it++)
  {
    auto inSecondData = (*AVLTree.find(nameTwoGlossary)).second.find((*it).first);
    if (inSecondData == (*AVLTree.find(nameTwoGlossary)).second.end())
    {
      compTree.insert(*it);
    }
  }
  if (nameOneGlossary == nameNewGlossary)
  {
    AVLTree.erase(nameOneGlossary);
    AVLTree.insert(nameNewGlossary, compTree);
  }
  else
  {
    AVLTree.insert(nameNewGlossary, compTree);
  }
  if (AVLTree.find(nameNewGlossary) != AVLTree.end())
  {
    AVLTree.erase(nameNewGlossary);
  }
  AVLTree.insert(nameNewGlossary, compTree);
}

void mihalchenko::intersect(typeParam &AVLTree)
{
  std::string nameNewGlossary, nameOneGlossary, nameTwoGlossary;
  std::cin >> nameNewGlossary >> nameOneGlossary >> nameTwoGlossary;
  if (AVLTree.find(nameOneGlossary) == AVLTree.end() || AVLTree.find(nameTwoGlossary) == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree< long long, std::string > dicts{};
  for (auto it = (*AVLTree.find(nameOneGlossary)).second.begin(); it != (*AVLTree.find(nameOneGlossary)).second.end(); it++)
  {
    auto inSecondData = (*AVLTree.find(nameTwoGlossary)).second.find((*it).first);
    if (inSecondData != (*AVLTree.find(nameTwoGlossary)).second.end())
    {
      dicts.insert(*it);
    }
  }
  if (AVLTree.find(nameNewGlossary) != AVLTree.end())
  {
    AVLTree.erase(nameNewGlossary);
  }
  AVLTree.insert(nameNewGlossary, dicts);
}

void mihalchenko::unionAVL(typeParam &AVLTree)
{
  std::string nameNewGlossary, nameOneGlossary, nameTwoGlossary;
  std::cin >> nameNewGlossary >> nameOneGlossary >> nameTwoGlossary;
  if (AVLTree.find(nameOneGlossary) == AVLTree.end() || AVLTree.find(nameTwoGlossary) == AVLTree.end())
  {
    printInvalidCommand(std::cout);
    return;
  }
  mihalchenko::AVLTree< long long, std::string > dicts{};
  for (auto it = (*AVLTree.find(nameOneGlossary)).second.begin(); it != (*AVLTree.find(nameOneGlossary)).second.end(); it++)
  {
    dicts.insert(*it);
  }
  for (auto it = (*AVLTree.find(nameTwoGlossary)).second.begin(); it != (*AVLTree.find(nameTwoGlossary)).second.end(); it++)
  {
    if (dicts.find((*it).first) == dicts.end())
    {
      dicts.insert(*it);
    }
  }
  if (AVLTree.find(nameNewGlossary) != AVLTree.end())
  {
    AVLTree.erase(nameNewGlossary);
  }
  AVLTree.insert(nameNewGlossary, dicts);
}

void mihalchenko::insertDataToTree(typeParam &TreeAndLeaves, std::string &inputStr)
{
  AVLTree< long long, std::string > branchAndLeaves{};
  size_t pos = 0;
  std::string nameGlossary = resiveString(inputStr, pos, true);
  while (pos < inputStr.length())
  {
    long long key = std::stoll(resiveString(inputStr, pos, false));
    std::string value = resiveString(inputStr, pos, true);
    branchAndLeaves.insert(key, value);
  }
  TreeAndLeaves.insert(nameGlossary, branchAndLeaves);
}
