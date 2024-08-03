#include "commands.hpp"
#include <string>

void zheleznyakov::commands::print(std::istream & in, std::ostream & out, const dicts_t & dicts)
{
  std::string dictName;
  in >> dictName;
  auto dict = dicts[dictName];
  if (dict.empty())
  {
    outEmpty(out);
    return;
  }
  out << dictName << ' ';
  auto it = dict.cbegin();
  while (it != dict.cend())
  {
    out << it->first << ' ' << it->second;
    out << (++it == dict.end() ? '\n' : ' ');
  }
}

void zheleznyakov::commands::complement(std::istream & in, std::ostream & out, dicts_t & dicts)
{
  std::string newDictName;
  in >> newDictName;
  std::string firstDictName;
  in >> firstDictName;
  std::string secondDictName;
  in >> secondDictName;
  auto firstDict = dicts.find(firstDictName);
  auto secondDict = dicts.find(secondDictName);
  if (firstDict == dicts.end() || secondDict == dicts.end())
  {
    outInvalidCommand(out);
    return;
  }
  dict_t newDict;
  for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it)
  {
    if (secondDict->second.find(it->first) == secondDict->second.end())
    {
      newDict[it->first] = it->second;
    }
  }
  for (auto it = secondDict->second.begin(); it != secondDict->second.end(); ++it)
  {
    if (firstDict->second.find(it->first) == firstDict->second.end())
    {
      newDict[it->first] = it->second;
    }
  }
  if (dicts.find(newDictName) != dicts.end())
  {
    dicts.erase(newDictName);
  }
  dicts.insert(newDictName, newDict);
}

void zheleznyakov::commands::intersect(std::istream & in, std::ostream & out, dicts_t & dicts)
{
  std::string newDictName;
  in >> newDictName;
  std::string firstDictName;
  in >> firstDictName;
  std::string secondDictName;
  in >> secondDictName;
  auto firstDict = dicts.find(firstDictName);
  auto secondDict = dicts.find(secondDictName);
  if (firstDict == dicts.end() || secondDict == dicts.end())
  {
    outInvalidCommand(out);
    return;
  }
  dict_t newDict;
  for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it)
  {
    if (secondDict->second.find(it->first) != secondDict->second.end())
    {
      newDict[it->first] = it->second;
    }
  }
  if (dicts.find(newDictName) != dicts.end())
  {
    dicts.erase(newDictName);
  }
  dicts.insert(newDictName, newDict);
}

void zheleznyakov::commands::append(std::istream & in, std::ostream & out, dicts_t & dicts)
{
  std::string newDictName;
  in >> newDictName;
  std::string firstDictName;
  in >> firstDictName;
  std::string secondDictName;
  in >> secondDictName;
  auto firstDict = dicts.find(firstDictName);
  auto secondDict = dicts.find(secondDictName);
  if (firstDict == dicts.end() || secondDict == dicts.end())
  {
    outInvalidCommand(out);
    return;
  }
  dict_t newDict;
  for (auto it = secondDict->second.begin(); it != secondDict->second.end(); ++it)
  {
    newDict[it->first] = it->second;
  }
  for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it)
  {
    newDict[it->first] = it->second;
  }
  if (dicts.find(newDictName) != dicts.end())
  {
    dicts.erase(newDictName);
  }
  dicts.insert(newDictName, newDict);
}

void zheleznyakov::outInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

void zheleznyakov::outEmpty(std::ostream & out)
{
  out << "<EMPTY>\n";
}
