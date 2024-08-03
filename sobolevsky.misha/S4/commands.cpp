#include "commands.hpp"
#include "utils.hpp"
#include <limits>
#include <string>

using bigTreeDeclaration = sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< int, std::string, int >, int >;
using smallTreeDeclaration = sobolevsky::AVLtree< int, std::string, int >;

void sobolevsky::getPrint(std::istream &in, std::ostream &out, bigTreeDeclaration &data)
{
  std::string name;
  in >> name;
  smallTreeDeclaration currTree(data.at(name));
  if (currTree.getSize() == 0)
  {
    errorEmpty(out);
    return;
  }
  out << name << " ";
  for (smallTreeDeclaration::ConstIterator iter(currTree.cbegin()); iter != currTree.cend();)
  {
    out << iter->first << " " << iter->second;
    iter++;
    out << (iter != currTree.cend() ? " " : "\n");
  }
}

void sobolevsky::getComplement(std::istream &in, bigTreeDeclaration &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  smallTreeDeclaration newTree;
  if (data.at(name1).getSize() != 0 && data.at(name2).getSize() != 0)
  {
    for (smallTreeDeclaration::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      if (data.at(name2).find(iter->first) == data.at(name2).end())
      {
        newTree.insert(std::make_pair(iter->first, iter->second));
      }
    }
  }

  checkName(data, newTree, newName);
}

void sobolevsky::getIntersect(std::istream &in, bigTreeDeclaration &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  smallTreeDeclaration newTree;
  if (data.at(name1).getSize() != 0 && data.at(name2).getSize() != 0)
  {
    for (smallTreeDeclaration::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      if (data.at(name2).find(iter->first) != data.at(name2).end())
      {
        newTree.insert(std::make_pair(iter->first, iter->second));
      }
    }
  }

  checkName(data, newTree, newName);
}

void sobolevsky::getUnion(std::istream &in, bigTreeDeclaration &data)
{
  std::string newName;
  std::string name1;
  std::string name2;
  in >> newName >> name1 >> name2;
  smallTreeDeclaration newTree;
  if (data.at(name1).getSize() != 0 && data.at(name2).getSize() == 0)
  {
    for (smallTreeDeclaration::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }
  }
  else if (data.at(name1).getSize() == 0 && data.at(name2).getSize() != 0)
  {
    for (smallTreeDeclaration::ConstIterator iter(data.at(name2).cbegin()); iter != data.at(name2).cend(); iter++)
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }
  }
  else if (data.at(name1).getSize() != 0 || data.at(name2).getSize() != 0)
  {
    for (smallTreeDeclaration::ConstIterator iter(data.at(name1).cbegin()); iter != data.at(name1).cend(); iter++)
    {
      newTree.insert(std::make_pair(iter->first, iter->second));
    }

    for (smallTreeDeclaration::ConstIterator iter(data.at(name2).cbegin()); iter != data.at(name2).cend(); iter++)
    {
      if (data.at(name1).find(iter->first) == data.at(name1).end())
      {
        newTree.insert(std::make_pair(iter->first, iter->second));
      }
    }
  }

  checkName(data, newTree, newName);
}
