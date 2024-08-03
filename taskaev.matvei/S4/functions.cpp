#include <iostream>
#include <string>
#include "functions.hpp"

namespace taskaev
{
  void createTree(std::istream& in, Tree& tree)
  {
    while (!in.eof())
    {
      std::string data = "";
      std::getline(in, data);
      if (!data.empty())
      {
        std::string temps = "";
        std::string names = "";
        size_t key = 0;
        std::string val = "";
        BSTree< size_t, std::string > tre;
        bool flag = true;
        size_t i = 0;
        while (i < data.length())
        {
          if (data[i] != ' ')
          {
            temps += data[i];
          }
          else if (data[i] == ' ' && flag == true)
          {
            names = temps;
            temps = "";
            flag = false;
          }
          else
          {
            if (std::isdigit(temps[0]))
            {
              key = std::stoll(temps);
              temps = "";
            }
            else
            {
              val = temps;
              temps = "";
              tre.insert(key, val);
            }
          }
          i++;
        }
        if (key == 0)
        {
          names = temps;
        }
        if (!val.empty())
        {
          val = temps;
          tre.insert(key, val);
        }
        tree.insert(names, tre);
      }
    }
  }

  void print(Tree& tree)
  {
    std::string datas = "";
    std::cin >> datas;
    BSTree< size_t, std::string > tres = tree.at(datas);
    if (tres.empty())
    {
      errorEmpty(std::cout);
      return;
    }
    else
    {
      BSTree< size_t, std::string >::ConstIterator it = tres.cbegin();
      BSTree< size_t, std::string >::ConstIterator end = tres.cend();
      std::cout << datas << " ";
      while (it != end)
      {
        std::pair< size_t, std::string > pair = *it;
        std::cout << pair.first << " " << pair.second;
        ++it;
        if (it != end)
        {
          std::cout << " ";
        }
        else
        {
          std::cout << "\n";
        }
      }
    }
  }

  void complement(Tree& tree)
  {
    std::string names, oneName, twoName;
    std::cin >> names >> oneName >> twoName;
    BSTree< size_t, std::string > tres;
    if (oneName == twoName)
    {
      tree.insert(names, tres);
      return;
    }
    findComplement(tree.at(oneName), tree.at(twoName), tres);
    if (names != oneName && names != twoName)
    {
      tree.insert(names, tres);
    }
    else if (names == oneName)
    {
      tree.erase(oneName);
      tree.insert(names, tres);
    }
    else
    {
      tree.erase(twoName);
      tree.insert(names, tres);
    }
  }

  void findComplement(SubTree& one, SubTree& two, SubTree& tres)
  {
    for (auto it = one.begin(); it != one.end(); ++it)
    {
      bool flag = false;
      for (auto iter = two.begin(); iter != two.end(); ++iter)
      {
        if (it->first == iter->first)
        {
          flag = true;
          break;
        }
      }
      if (!flag)
      {
        tres.insert(*it);
      }
    }
  }

  void intersect(Tree& tree)
  {
    std::string names, oneName, twoName;
    std::cin >> names >> oneName >> twoName;
    BSTree< size_t, std::string > tres;
    BSTree< size_t, std::string > oneTres = tree.at(oneName);
    BSTree< size_t, std::string > twoTres = tree.at(twoName);
    if (!oneTres.empty() == 0 || !twoTres.empty() == 0)
    {
      tree.erase(names);
      tree.insert(names, tres);
      return;
    }
    for (auto it = oneTres.begin(); it != oneTres.end(); ++it)
    {
      size_t key = it->first;
      if (twoTres.find(key) != twoTres.cend())
      {
        tres.insert(*it);
      }
    }
    if (names != oneName && names != twoName)
    {
      tree.insert(names, tres);
    }
    else if (names == oneName)
    {
      tree.erase(oneName);
      tree.insert(names, tres);
    }
    else
    {
      tree.erase(twoName);
      tree.insert(names, tres);
    }
  }

  SubTree mergeTrees(SubTree& treeOne, SubTree& treeTwo)
  {
    BSTree< size_t, std::string > result;
    auto itOne = treeOne.begin();
    auto itTwo = treeTwo.begin();

    while (itOne != treeOne.end() || itTwo != treeTwo.end())
    {
      if (itOne != treeOne.end() && (itTwo == treeTwo.end() || itOne->first < itTwo->first))
      {
        result.insert(*itOne);
        ++itOne;
      }
      else if (itTwo != treeTwo.end() && (itOne == treeOne.end() || itTwo->first < itOne->first))
      {
        result.insert(*itTwo);
        ++itTwo;
      }
      else
      {
        result.insert(*itOne);
        ++itOne;
        ++itTwo;
      }
    }
    return result;
  }

  void unions(Tree& tree)
  {
    std::string names, oneName, twoName;
    std::cin >> names >> oneName >> twoName;
    BSTree<size_t, std::string> tres = mergeTrees(tree.at(oneName), tree.at(twoName));
    if (names != oneName && names != twoName)
    {
      tree.insert(names, tres);
    }
    else if (names == oneName)
    {
      tree.erase(oneName);
      tree.insert(names, tres);
    }
    else
    {
      tree.erase(twoName);
      tree.insert(names, tres);
    }
  }

  void errorInvalid(std::ostream& out)
  {
    out << "<INVALID COMMAND>\n";
  }

  void errorEmpty(std::ostream& out)
  {
    out << "<EMPTY>\n";
  }
}
