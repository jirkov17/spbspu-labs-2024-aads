#include "utils.hpp"

using bigTreeDeclaration = sobolevsky::AVLtree< std::string, sobolevsky::AVLtree< int, std::string, int >, int >;
using smallTreeDeclaration = sobolevsky::AVLtree< int, std::string, int >;

void sobolevsky::inputFromFile(std::istream &file, bigTreeDeclaration &data)
{
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    std::string name;
    file >> name;
    smallTreeDeclaration tempTree;
    int key;
    while (file >> key)
    {
      std::string value;
      file >> value;
      tempTree.insert(std::make_pair(key, value));
    }
    data.insert(std::make_pair(name, tempTree));
  }
}

void sobolevsky::errorInvalidCommand(std::ostream &out)
{
  out << "<INVALID COMMAND>\n";
}

void sobolevsky::errorEmpty(std::ostream &out)
{
  out << "<EMPTY>\n";
}

void sobolevsky::checkName(bigTreeDeclaration &data, smallTreeDeclaration &newTree, std::string newName)
{
  if (data.find(newName) != data.end())
  {
    data.at(newName).swap(newTree);
    newTree.clear();
  }
  else
  {
    data.insert(std::make_pair(newName, newTree));
  }
}
