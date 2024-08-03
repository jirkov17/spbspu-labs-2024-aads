#include "Commands.hpp"
#include <string>
#include <sstream>
#include "ErrorMessage.hpp"

namespace sukacheva
{
  void inputTree(treeOfTrees& treeOfDicts, std::string& line)
  {
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    if (name.empty())
    {
      return;
    }
    BST< size_t, std::string > currentDict;
    size_t key;
    std::string value;
    while (iss >> key >> value)
    {
      currentDict.insert(key, value);
    }
    treeOfDicts.insert(name, currentDict);
  }

  void print(treeOfTrees& treeOfDicts, std::string name, std::ostream& out)
  {
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    if (treeOfDicts.find(name) == nullptr)
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    BST< size_t, std::string > dict = treeOfDicts.find(name)->second;
    using iterator = BST< size_t, std::string >::Iterator;
    if (dict.empty())
    {
      EmptyMessage(out);
      return;
    }
    out << name << " ";
    size_t counter = 0;
    for (iterator it = dict.begin(); it != dict.end(); it++)
    {
      out << it->first << " " << it->second;
      counter++;
      if (counter != dict.size())
      {
        out << " ";
      }
      else
      {
        out << "\n";
      }
    }
  }

  void printCommand(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string name;
    in >> name;
    if (in.fail())
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    print(treeOfDicts, name, out);
  }

  void comlement(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string nameNew;
    std::string nameFirst;
    std::string nameSecond;
    in >> nameNew >> nameFirst >> nameSecond;
    if (in.fail())
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    if (treeOfDicts.find(nameSecond) == nullptr || treeOfDicts.find(nameFirst) == nullptr)
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    BST< size_t, std::string > secondDict = treeOfDicts.find(nameSecond)->second;
    BST< size_t, std::string > firstDict = treeOfDicts.find(nameFirst)->second;
    BST< size_t, std::string > newDict;
    using iterator = BST< size_t, std::string >::Iterator;
    for (iterator it = firstDict.begin(); it != firstDict.end(); it++)
    {
      if (secondDict.find(it->first) == nullptr)
      {
        newDict.insert(it->first, it->second);
      }
    }
    if (treeOfDicts.find(nameNew) != nullptr)
    {
      treeOfDicts.erase(nameNew);
    }
    treeOfDicts.insert(nameNew, newDict);
  }

  void intersect(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string nameNew;
    std::string nameFirst;
    std::string nameSecond;
    in >> nameNew >> nameFirst >> nameSecond;
    if (in.fail())
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    if (treeOfDicts.find(nameSecond) == nullptr || treeOfDicts.find(nameFirst) == nullptr)
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    BST< size_t, std::string > secondDict = treeOfDicts.find(nameSecond)->second;
    BST< size_t, std::string > firstDict = treeOfDicts.find(nameFirst)->second;
    BST< size_t, std::string > newDict;
    using iterator = BST< size_t, std::string >::Iterator;
    for (iterator it = firstDict.begin(); it != firstDict.end(); it++)
    {
      if (secondDict.find(it->first) != nullptr)
      {
        newDict.insert(it->first, it->second);
      }
    }
    if (treeOfDicts.find(nameNew) != nullptr)
    {
      treeOfDicts.erase(nameNew);
    }
    treeOfDicts.insert(nameNew, newDict);
  }

  void unionCommand(treeOfTrees& treeOfDicts, std::istream& in, std::ostream& out)
  {
    std::string nameNew;
    std::string nameFirst;
    std::string nameSecond;
    in >> nameNew >> nameFirst >> nameSecond;
    if (in.fail())
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    if (treeOfDicts.empty())
    {
      EmptyMessage(out);
      return;
    }
    if (treeOfDicts.find(nameSecond) == nullptr || treeOfDicts.find(nameFirst) == nullptr)
    {
      throw std::logic_error("<WRONG INPUT>\n");
    }
    BST< size_t, std::string > secondDict = treeOfDicts.find(nameSecond)->second;
    BST< size_t, std::string > newDict = treeOfDicts.find(nameFirst)->second;
    using iterator = BST< size_t, std::string >::Iterator;
    for (iterator secit = secondDict.begin(); secit != secondDict.end(); secit++)
    {
      newDict.insert(secit->first, secit->second);
    }
    if (treeOfDicts.find(nameNew) != nullptr)
    {
      treeOfDicts.erase(nameNew);
    }
    treeOfDicts.insert(nameNew, newDict);
  }
}
