#include "execCommands.hpp"

std::ostream& psarev::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& psarev::outEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
  return out;
}

void psarev::fillTree(std::istream& in, avlTree< std::string, base_t >& dataSets)
{
  while (!in.eof())
  {
    if (in.fail())
    {
      in.clear();
    }

    std::string setName;
    int key;
    in >> setName;
    psarev::avlTree< int, std::string > curSet;

    while (in >> key)
    {
      std::string value;
      in >> value;
      curSet.insert({ key, value });
    }

    dataSets.insert({ setName, curSet });
  }
}

void psarev::print(avlTree< std::string, avlTree< int, std::string > >& dataSets)
{
  std::string setName;
  std::cin >> setName;

  auto setIter = dataSets.find(setName);
  if (setIter == dataSets.end())
  {
    outInvCommand(std::cout);
    return;
  }
  else if ((*setIter).second.isEmpty())
  {
    outEmpty(std::cout);
    return;
  }

  std::cout << (*setIter).first << " ";
  for (auto it = (*setIter).second.begin(); it != (*setIter).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    ((++it) == (*setIter).second.end()) ? std::cout << "\n" : std::cout << ' ';
    it--;
  }
}

void psarev::complement(avlTree< std::string, avlTree< int, std::string > >& dataSets)
{
  std::string newSet, fSet, sSet;
  std::cin >> newSet >> fSet >> sSet;

  auto fSetIter = dataSets.find(fSet);
  auto sSetIter = dataSets.find(sSet);
  if ((fSetIter == dataSets.end()) || (sSetIter == dataSets.end()))
  {
    outInvCommand(std::cout);
    return;
  }

  avlTree< int, std::string > resSet;
  for (auto iter = (*fSetIter).second.begin(); iter != (*fSetIter).second.end(); iter++)
  {
    auto newIter = (*dataSets.find(sSet)).second.find((*iter).first);
    if (newIter == (*dataSets.find(sSet)).second.end())
    {
      resSet.insert(*iter);
    }
  }

  auto checkIter = dataSets.find(newSet);
  if (checkIter != dataSets.end())
  {
    dataSets.erase(newSet);
  }
  dataSets.insert({ newSet, resSet });
}

void psarev::intersect(avlTree<std::string, psarev::avlTree<int, std::string>>& dataSets)
{
  std::string newSet, fSet, sSet;
  std::cin >> newSet >> fSet >> sSet;

  auto fSetIter = dataSets.find(fSet);
  auto sSetIter = dataSets.find(sSet);
  if (fSetIter == dataSets.end() || sSetIter == dataSets.end())
  {
    outInvCommand(std::cout);
    return;
  }

  avlTree< int, std::string > resSet;
  for (auto iter = (*fSetIter).second.begin(); iter != (*fSetIter).second.end(); iter++)
  {
    auto interSSetIter = (*dataSets.find(sSet)).second.find((*iter).first);
    if (interSSetIter != (*dataSets.find(sSet)).second.end())
    {
      resSet.insert(*iter);
    }
  }

  auto checkIter = dataSets.find(newSet);
  if (checkIter != dataSets.end())
  {
    dataSets.erase(newSet);
  }
  dataSets.insert({ newSet, resSet });
}

void psarev::unio(avlTree<std::string, avlTree<int, std::string>>& dataSets)
{
  std::string newSet, fSet, sSet;
  std::cin >> newSet >> fSet >> sSet;

  auto fSetIter = dataSets.find(fSet);
  auto sSetIter = dataSets.find(sSet);
  if (fSetIter == dataSets.end() || sSetIter == dataSets.end())
  {
    outInvCommand(std::cout);
    return;
  }

  avlTree< int, std::string > resSet;
  for (auto iter = (*fSetIter).second.begin(); iter != (*fSetIter).second.end(); iter++)
  {
    resSet.insert(*iter);
  }
  for (auto iter = (*sSetIter).second.begin(); iter != (*sSetIter).second.end(); iter++)
  {
    auto setIter = resSet.find((*iter).first);
    if (setIter == resSet.end())
    {
      resSet.insert(*iter);
    }
  }

  auto checkIter = dataSets.find(newSet);
  if (checkIter != dataSets.end())
  {
    dataSets.erase(newSet);
  }
  dataSets.insert({ newSet, resSet });
}
