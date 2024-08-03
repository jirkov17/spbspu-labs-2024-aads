#include "commands.hpp"

std::string nikiforov::cutElem(std::string& str)
{
  std::string elem = str.substr(0, str.find_first_of(" ", 0));
  if (str.find_first_of(" ") == std::string::npos)
  {
    str = "";
  }
  else
  {
    str = str.substr(str.find_first_of(" ") + 1);
  }
  return elem;
}

void nikiforov::createDictionary(std::string& strVocab, AvlTree< int, std::string >& dict)
{
  std::string key;
  std::string value;

  while (!strVocab.empty())
  {
    key = cutElem(strVocab);
    value = cutElem(strVocab);
    dict.emplace(stoi(key), value);
  }
}

void nikiforov::print(dictionariesTree& dictionaries, std::istream& in, std::ostream& out)
{
  std::string nameDict;
  in >> nameDict;
  auto dict = dictionaries.find(nameDict);

  if (dict != dictionaries.end())
  {
    if (!dict->second.is_empty())
    {
      out << dict->first;
      for (auto it = dict->second.begin(); it != dict->second.end(); ++it)
      {
        out << " " << it->first << " " << it->second;
      }
      out << "\n";
    }
    else
    {
      emptyMessage(out);
    }
  }
  else
  {
    errorMessage(out);
  }
}

void nikiforov::complement(dictionariesTree& dictionaries, std::istream& in, std::ostream& out)
{
  std::string newNameDict, firstName, secondName;
  in >> newNameDict >> firstName >> secondName;
  auto firstDict = dictionaries.find(firstName);
  auto secondDict = dictionaries.find(secondName);

  if (firstDict != dictionaries.end() && secondDict != dictionaries.end())
  {
    AvlTree< int, std::string > newDict;
    for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it)
    {
      if (secondDict->second.find(it->first) == secondDict->second.end())
      {
        newDict.emplace(it->first, it->second);
      }
    }

    auto findSameDict = dictionaries.find(newNameDict);
    if (findSameDict != dictionaries.end())
    {
      dictionaries.erase(findSameDict->first);
    }
    dictionaries.emplace(newNameDict, newDict);
  }
  else
  {
    errorMessage(out);
  }
}

void nikiforov::intersect(dictionariesTree& dictionaries, std::istream& in, std::ostream& out)
{
  std::string newNameDict, firstName, secondName;
  in >> newNameDict >> firstName >> secondName;
  auto firstDict = dictionaries.find(firstName);
  auto secondDict = dictionaries.find(secondName);

  if (firstDict != dictionaries.end() && secondDict != dictionaries.end())
  {
    AvlTree< int, std::string > newDict;
    for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it)
    {
      if (secondDict->second.find(it->first) != secondDict->second.end())
      {
        newDict.emplace(it->first, it->second);
      }
    }

    auto findSameDict = dictionaries.find(newNameDict);
    if (findSameDict != dictionaries.end())
    {
      dictionaries.erase(findSameDict->first);
    }
    dictionaries.emplace(newNameDict, newDict);
  }
  else
  {
    errorMessage(out);
  }
}

void nikiforov::unite(dictionariesTree& dictionaries, std::istream& in, std::ostream& out)
{
  std::string newNameDict, firstName, secondName;
  in >> newNameDict >> firstName >> secondName;
  auto firstDict = dictionaries.find(firstName);
  auto secondDict = dictionaries.find(secondName);

  if (firstDict != dictionaries.end() && firstDict != dictionaries.end())
  {
    AvlTree< int, std::string > newDict;
    for (auto it = firstDict->second.begin(); it != firstDict->second.end(); ++it)
    {
      newDict.emplace(it->first, it->second);
    }
    for (auto it = secondDict->second.begin(); it != secondDict->second.end(); ++it)
    {
      if (newDict.find(it->first) == newDict.end())
      {
        newDict.emplace(it->first, it->second);
      }
    }

    auto findSameDict = dictionaries.find(newNameDict);
    if (findSameDict != dictionaries.end())
    {
      dictionaries.erase(findSameDict->first);
    }
    dictionaries.emplace(newNameDict, newDict);
  }
  else
  {
    errorMessage(out);
  }
}

std::ostream& nikiforov::errorMessage(std::ostream& out)
{
  return out << "<INVALID COMMAND>\n";
}

std::ostream& nikiforov::emptyMessage(std::ostream& out)
{
  return out << "<EMPTY>\n";
}
