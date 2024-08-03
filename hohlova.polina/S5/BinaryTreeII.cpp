#include "BinaryTreeII.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <BinarySearchTree.hpp>

void hohlova::readFile(const std::string& path, BinarySearchTree< int, std::string >& bst)
{
  if (path.empty())
  {
    throw std::runtime_error("Path is empty\n");
  }
  std::ifstream file(path);
  if (!file.is_open())
  {
    throw std::runtime_error("File not open\n");
  }
  std::string line;
  while (!file.eof())
  {
    std::getline(file, line);
    hohlova::readDataSet(line, bst);
  }
  file.close();
}

int hohlova::parseNum(const std::string& num)
{
  int result = 0;
  result = std::stoi(num);
  return result;
}

void hohlova::readDataSet(const std::string& dataSet, BinarySearchTree< int, std::string >& bst)
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
  size_t i = 0;
  while (i < stringList.size() - 1)
  {
    bst.push(parseNum(stringList[i]), stringList[i + 1]);
    i += 2;
  }
}

int hohlova::sum(int a, int b)
{
  if (b > 0 && a > INT32_MAX - b)
  {
    throw std::runtime_error("Sum overflow");
  }
  else if (b < 0 && a < INT32_MIN - b)
  {
    throw std::runtime_error("Sum underflow");
  }
  return a + b;
}
