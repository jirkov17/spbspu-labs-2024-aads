#include "WorkerBST.hpp"
#include <fstream>
#include <string>

void clearTree(Dictionary& bst)
{
  auto it = bst.begin();

  while (it != bst.end())
  {
    auto ptr = (*it).second;
    delete  ptr;
    ++it;
  }
}

void Menu(Dictionary& bst)
{
  std::string line;
  while (!std::cin.eof())
  {
    std::getline(std::cin, line);
    if (!line.empty())
    {
      parseArguments(bst, line);
    }
  }
}
void readFile(Dictionary& bst, const std::string& path)
{
  if (path.empty())
  {
    std::runtime_error("Path is empty\n");
  }
  std::ifstream file(path);
  if (!file.is_open())
  {
    std::runtime_error("File not open\n");
  }
  std::string line;
  while (!file.eof())
  {
    std::getline(file, line);
    readDataSet(bst, line);
  }
  file.close();
}

void print(Dictionary& bst, const std::string& str)
{
  BinarySearchTree< int, std::string >* findBst = nullptr;
  findBst = bst.get(str);
  if (findBst == nullptr)
  {
    warningInvCom(std::cout);
    return;
  }
  else if (findBst->empty())
  {
    warningEmpty(std::cout);
    return;
  }
  auto it = findBst->begin();
  std::cout << str << ' ';
  for (; it != findBst->end();)
  {
    std::cout << (*it).first << ' ' << (*it).second;
    if (++it != findBst->end())
    {
      std::cout << ' ';
    }
  }
  std::cout << '\n';
}

void complement(Dictionary& bst, std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end)
{
  BinarySearchTree< int, std::string >* first = nullptr;
  BinarySearchTree< int, std::string >* second = nullptr;
  std::string key = *begin;
  ++begin;

  while (begin != end)
  {
    if (!first)
    {
      first = bst.get(*begin);
    }
    else if (!second)
    {
      second = bst.get(*begin);
    }
    if (first && second)
    {
      break;
    }
    ++begin;
  }
  if (!second || !first)
  {
    warningInvCom(std::cout);
    return;
  }
  BinarySearchTree< int, std::string >* result = new BinarySearchTree< int, std::string >;
  auto itF = first->begin();
  auto itE = first->end();

  while (itF != itE)
  {
    auto res = second->contains((*itF).first);
    if (!res)
    {
      result->push((*itF).first, (*itF).second);
    }
    ++itF;
  }

  if (bst.contains(key))
  {
    delete bst.get(key);
    bst.drop(key);
  }
  bst.push(key, result);
}

int parseNum(const std::string& num)
{
  size_t pos = 0;
  auto symbol = static_cast< unsigned char >(num[pos]);
  long long result = 0;
  while (std::isdigit(symbol))
  {
    result = result * 10 + (symbol - '0');
    if (pos == num.size() - 1)
    {
      pos++;
      break;
    }
    symbol = static_cast< unsigned char >(num[++pos]);
  }
  return result;
}

void readDataSet(Dictionary& bst, const std::string& dataSet)
{
  size_t pos = 0;
  std::string word;
  word.reserve(10);
  std::vector< std::string > stringList;
  stringList.reserve(10);
  while (pos <= dataSet.size())
  {
    if (std::isspace(dataSet[pos]) || pos == dataSet.size())
    {
      stringList.push_back(word);
      word = "";
    }
    else
    {
      word += dataSet[pos];
    }
    ++pos;
  }

  size_t i = 1;
  BinarySearchTree< int, std::string >* newTree = new BinarySearchTree< int, std::string >;
  bst.push(stringList[0], newTree);
  while (i < stringList.size() - 1)
  {
    newTree->push(parseNum(stringList[i]), stringList[i + 1]);
    i += 2;
  }
}

void intersect(Dictionary& bst, std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end)
{
  BinarySearchTree< int, std::string >* first = nullptr;
  BinarySearchTree< int, std::string >* second = nullptr;
  std::string key = *begin;
  ++begin;

  while (begin != end)
  {
    if (!first)
    {
      first = bst.get(*begin);
    }
    else if (!second)
    {
      second = bst.get(*begin);
    }
    ++begin;
  }
  if (!second || !first)
  {
    warningInvCom(std::cout);
    return;
  }
  BinarySearchTree< int, std::string >* result = new BinarySearchTree< int, std::string >;
  auto itF = first->begin();
  while (itF != first->end())
  {
    auto res = second->contains((*itF).first);
    if (res)
    {
      result->push((*itF).first, (*itF).second);
    }
    ++itF;
  }

  if (bst.contains(key))
  {
    delete bst.get(key);
    bst.drop(key);
  }
  bst.push(key, result);
}

void unify(Dictionary& bst, std::vector< std::string >::iterator begin, std::vector< std::string >::iterator end)
{
  BinarySearchTree< int, std::string >* first = nullptr;
  BinarySearchTree< int, std::string >* second = nullptr;
  std::string key = *begin;
  ++begin;

  while (begin != end)
  {
    if (!first)
    {
      first = bst.get(*begin);
    }
    else if (!second)
    {
      second = bst.get(*begin);
    }
    ++begin;
  }

  if (!second || !first)
  {
    warningInvCom(std::cout);
    return;
  }
  BinarySearchTree< int, std::string >* result = new BinarySearchTree< int, std::string >;
  auto itF = first->begin();
  auto itS = second->begin();

  while (itF != first->end() || itS != second->end())
  {
    if (itF != first->end())
    {
      if (!result->contains((*itF).first))
      {
        result->push((*itF).first, (*itF).second);
      }
      ++itF;
    }

    if (itS != second->end())
    {
      if (!result->contains((*itS).first))
      {
        result->push((*itS).first, (*itS).second);
      }
      ++itS;
    }
  }

  if (bst.contains(key))
  {
    delete bst.get(key);
    bst.drop(key);
  }
  bst.push(key, result);
}

void parseArguments(Dictionary& bst, const std::string& str)
{
  size_t pos = 0;
  std::string word;
  word.reserve(10);
  std::vector< std::string > stringList;
  stringList.reserve(10);

  while (pos <= str.size())
  {
    if (std::isspace(str[pos]) || pos == str.size())
    {
      stringList.push_back(word);
      word = "";
    }
    else
    {
      word += str[pos];
    }
    ++pos;
  }

  word = stringList.front();
  if (word == "print")
  {
    print(bst, *(stringList.begin() + 1));
  }
  else if (word == "intersect")
  {
    intersect(bst, stringList.begin() + 1, stringList.end());
  }
  else if (word == "complement")
  {
    complement(bst, stringList.begin() + 1, stringList.end());
  }
  else if (word == "union")
  {
    unify(bst, stringList.begin() + 1, stringList.end());
  }
  else if (word != "")
  {
    std::cout << "<INVALID COMMAND>" << '\n';
  }
}

void warningEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}

void warningInvCom(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}
