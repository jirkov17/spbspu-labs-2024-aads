#include "commands.hpp"
#include <string>
#include <iostream>
#include <cctype>

std::string khoroshkin::getString(std::string & line, size_t & pos)
{
  std::string result = "";
  while (pos < line.length() && line[pos] != ' ')
  {
    result += line[pos++];
  }
  pos++;
  return result;
}

long long khoroshkin::getKey(std::string & line, size_t & pos)
{
  std::string result = "";
  while (pos < line.length() && line[pos] != ' ' && (std::isdigit(line[pos]) || line[pos] == '-'))
  {
    result += line[pos++];
  }
  pos++;
  return std::stoll(result);
}

void khoroshkin::print(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree)
{
  std::string name;
  std::cin >> name;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  auto outEmpty = std::bind(outMessage, std::placeholders::_1, "<EMPTY>\n");
  auto dataset = Tree.find(name);
  if (dataset == Tree.end())
  {
    outInvalid(std::cout);
    return;
  }
  else if ((*dataset).second.isEmpty())
  {
    outEmpty(std::cout);
    return;
  }

  std::cout << (*dataset).first << " ";
  for (auto it = (*dataset).second.begin(); it != (*dataset).second.end(); ++it)
  {
    std::cout << (*it).first << " " << (*it).second;
    ((++it) == (*dataset).second.end()) ? std::cout << "\n" : std::cout << ' ';
    it--;
  }
}

void khoroshkin::complement(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  auto firstData = Tree.find(nameFirst);
  auto secondData = Tree.find(nameSecond);
  if (firstData == Tree.end() || secondData == Tree.end())
  {
    outInvalid(std::cout);
    return;
  }
  khoroshkin::Tree< long long, std::string > datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    auto inSecondData = (*Tree.find(nameSecond)).second.find((*it).first);
    if (inSecondData == (*Tree.find(nameSecond)).second.end())
    {
      datasets.insert(*it);
    }
  }
  if (nameFirst == name)
  {
    Tree.erase(nameFirst);
    Tree.insert(name, datasets);
  }
  else
  {
    Tree.insert(name, datasets);
  }
}

void khoroshkin::intersect(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  auto firstData = Tree.find(nameFirst);
  auto secondData = Tree.find(nameSecond);
  if (firstData == Tree.end() || secondData == Tree.end())
  {
    outInvalid(std::cout);
    return;
  }
  khoroshkin::Tree< long long, std::string > datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    auto inSecondData = (*Tree.find(nameSecond)).second.find((*it).first);
    if (inSecondData != (*Tree.find(nameSecond)).second.end())
    {
      datasets.insert(*it);
    }
  }
  if (nameFirst == name)
  {
    Tree.erase(nameFirst);
    Tree.insert(name, datasets);
  }
  else
  {
    Tree.insert(name, datasets);
  }
}

void khoroshkin::unite(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree)
{
  std::string name, nameFirst, nameSecond;
  std::cin >> name >> nameFirst >> nameSecond;
  auto outInvalid = std::bind(outMessage, std::placeholders::_1, "<INVALID COMMAND>\n");
  auto firstData = Tree.find(nameFirst);
  auto secondData = Tree.find(nameSecond);
  if (firstData == Tree.end() || secondData == Tree.end())
  {
    outInvalid(std::cout);
    return;
  }
  khoroshkin::Tree< long long, std::string > datasets{};
  for (auto it = (*firstData).second.begin(); it != (*firstData).second.end(); it++)
  {
    datasets.insert(*it);
  }
  for (auto it = (*secondData).second.begin(); it != (*secondData).second.end(); it++)
  {
    auto inSet = datasets.find((*it).first);
    if (inSet == datasets.end())
    {
      datasets.insert(*it);
    }
  }
  if (nameFirst == name)
  {
    Tree.erase(nameFirst);
    Tree.insert(name, datasets);
  }
  else if (nameSecond == name)
  {
    Tree.erase(nameSecond);
    Tree.insert(name, datasets);
  }
  else
  {
    Tree.insert(name, datasets);
  }
}

void khoroshkin::outMessage(std::ostream & out, const std::string & message)
{
  out << message;
}
