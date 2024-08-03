#include "dataFunctions.hpp"
#include "inputFunctions.hpp"
#include <iostream>

int redko::cutKey(std::string & str)
{
  int key = std::stoi(str.substr(0, str.find_first_of(" ", 0)));
  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return key;
}

void redko::print(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr)
{
  std::string setName = redko::cutName(descr);
  if (!dataSets[setName].empty())
  {
    std::cout << setName;
    redko::BSTree< int, std::string >::iterator currElem = dataSets[setName].begin();
    while (currElem != dataSets[setName].end())
    {
      std::cout << ' ' << currElem->first << ' ' << currElem->second;
      ++currElem;
    }
    std::cout << '\n';
  }
  else
  {
    redko::printMessage(std::cout, "<EMPTY>");
  }
}

void redko::complement(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr)
{
  std::string newSetName = redko::cutName(descr);
  std::string firstSetName = redko::cutName(descr);
  std::string secondSetName = redko::cutName(descr);
  redko::BSTree< int, std::string > dataSet{};
  redko::BSTree< int, std::string >::iterator currElem = dataSets[firstSetName].begin();
  while (currElem != dataSets[firstSetName].end())
  {
    if (dataSets[secondSetName].find(currElem->first) == dataSets[secondSetName].end())
    {
      dataSet.insert(*currElem);
    }
    ++currElem;
  }
  currElem = dataSets[secondSetName].begin();
  while (currElem != dataSets[secondSetName].end())
  {
    if (dataSets[firstSetName].find(currElem->first) == dataSets[firstSetName].end())
    {
      dataSet.insert(*currElem);
    }
    ++currElem;
  }
  if (dataSets.find(newSetName) != dataSets.end())
  {
    dataSets.erase(newSetName);
  }
  dataSets.insert({ newSetName, dataSet });
}

void redko::intersect(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr)
{
  std::string newSetName = redko::cutName(descr);
  std::string firstSetName = redko::cutName(descr);
  std::string secondSetName = redko::cutName(descr);
  redko::BSTree< int, std::string > dataSet{};
  redko::BSTree< int, std::string >::iterator currElem = dataSets[firstSetName].begin();
  while (currElem != dataSets[firstSetName].end())
  {
    if (dataSets[secondSetName].find(currElem->first) != dataSets[secondSetName].end())
    {
      dataSet.insert(*currElem);
    }
    ++currElem;
  }
  if (dataSets.find(newSetName) != dataSets.end())
  {
    dataSets.erase(newSetName);
  }
  dataSets.insert({ newSetName, dataSet });
}

void redko::unite(BSTree< std::string, BSTree < int, std::string > > & dataSets, std::string & descr)
{
  std::string newSetName = redko::cutName(descr);
  std::string firstSetName = redko::cutName(descr);
  std::string secondSetName = redko::cutName(descr);
  redko::BSTree< int, std::string > dataSet = dataSets[firstSetName];
  redko::BSTree< int, std::string >::iterator currElem = dataSets[secondSetName].begin();
  while (currElem != dataSets[secondSetName].end())
  {
    dataSet.insert(*currElem);
    ++currElem;
  }
  if (dataSets.find(newSetName) != dataSets.end())
  {
    dataSets.erase(newSetName);
  }
  dataSets.insert({ newSetName, dataSet });
}

void redko::printMessage(std::ostream & out, const std::string & message)
{
  out << message << '\n';
}
