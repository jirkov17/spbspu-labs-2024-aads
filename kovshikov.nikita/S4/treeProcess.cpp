#include "treeProcess.hpp"
#include <functional>
#include <iostream>

bool kovshikov::isDigit(std::string str)
{
  size_t size = str.length();
  for(size_t i = 0; i < size; i++)
  {
    if(!std::isdigit(str[i]))
    {
      return false;
    }
  }
  return true;
}

void kovshikov::readData(std::istream& in, Tree< std::string, Tree< size_t, std::string > >& allTree)
{
  while(!in.eof())
  {
    std::string dictionary = "";
    std::getline(in, dictionary);
    if(!dictionary.empty())
    {
      createTree(allTree, dictionary);
    }
  }
}

void kovshikov::createTree(Tree< std::string, Tree< size_t, std::string > >& allTree, std::string dictionary)
{
  std::string temp = "";
  std::string name = "";
  size_t key = 0;
  std::string value = "";
  Tree< size_t, std::string > tree;
  bool isName = true;
  for(size_t i = 0; i < dictionary.length(); i++)
  {
    if(dictionary[i] != ' ')
    {
      temp += dictionary[i];
    }
    else if(dictionary[i] == ' ' && isName == true)
    {
      name = temp;
      temp = "";
      isName = false;
    }
    else
    {
      if(isDigit(temp) == true)
      {
        key = std::stoll(temp);
        temp = "";
      }
      else
      {
        value = temp;
        temp = "";
        tree.insert(key, value);
      }
    }
  }
  if(key == 0)
  {
    name = temp;
  }
  if(!value.empty())
  {
    value = temp;
    tree.insert(key, value);
  }
  allTree.insert(name, tree);
}

void kovshikov::print(Tree< std::string, Tree< size_t, std::string > >& allTree)
{
  std::string dictionary;
  std::cin >> dictionary;
  Tree< size_t, std::string > tree = allTree.at(dictionary);
  auto outEmpty = std::bind(outText, std::placeholders::_1, "<EMPTY>");
  if(tree.isEmpty())
  {
    outEmpty(std::cout);
  }
  else
  {
    Tree< size_t, std::string >::Iterator iterator = tree.begin();
    Tree< size_t, std::string >::Iterator end = tree.end();
    std::cout << dictionary << " ";
    while(iterator != end)
    {
      std::pair< size_t, std::string > pair = *iterator;
      if(++iterator == end)
      {
        std::cout << pair.first << " " << pair.second << "\n";
      }
      else
      {
        std::cout << pair.first << " " << pair.second << " ";
      }
    }
  }
}

void kovshikov::getComplement(Tree< std::string, Tree< size_t, std::string > >& allTree)
{
  std::string name;
  std::string  nameFirst;
  std::string  nameSecond;
  std:: cin >> name >> nameFirst >> nameSecond;
  Tree< size_t, std::string > newTree;
  Tree< size_t, std::string > firstDictionary = allTree.at(nameFirst);
  Tree< size_t, std::string > secondDictionary = allTree.at(nameSecond);
  Tree< size_t, std::string >::Iterator iteratorFirst = firstDictionary.begin();
  Tree< size_t, std::string >::Iterator endFirst = firstDictionary.end();
  Tree< size_t, std::string >::Iterator iteratorSecond = secondDictionary.begin();
  Tree< size_t, std::string >::Iterator endSecond = secondDictionary.end();
  while(iteratorFirst != endFirst)
  {
    std::pair< size_t, std::string > pair = *iteratorFirst;
    if(secondDictionary.find(pair.first) == endSecond)
    {
      newTree.insert(pair);
    }
    iteratorFirst++;
  }
  while(iteratorSecond != endSecond)
  {
    std::pair< size_t, std::string > pair = *iteratorSecond;
    if(firstDictionary.find(pair.first) == endFirst)
    {
      newTree.insert(pair);
    }
    iteratorSecond++;
  }
  allTree.insert(name, newTree);
}

void kovshikov::getIntersect(Tree< std::string, Tree< size_t, std::string > >& allTree)
{
  std::string name;
  std::string  nameFirst;
  std::string  nameSecond;
  std:: cin >> name >> nameFirst >> nameSecond;
  Tree< size_t, std::string > newTree;
  Tree< size_t, std::string > firstDictionary = allTree.at(nameFirst);
  Tree< size_t, std::string > secondDictionary = allTree.at(nameSecond);
  Tree< size_t, std::string >::Iterator iteratorFirst = firstDictionary.begin();
  Tree< size_t, std::string >::Iterator endFirst = firstDictionary.end();
  Tree< size_t, std::string >::Iterator endSecond = secondDictionary.end();
  while(iteratorFirst != endFirst)
  {
    std::pair< size_t, std::string > pair = *iteratorFirst;
    if(secondDictionary.find(pair.first) != endSecond)
    {
      newTree.insert(pair);
    }
    iteratorFirst++;
  }
  allTree.insert(name, newTree);
}

void kovshikov::getUnion(Tree< std::string, Tree< size_t, std::string > >& allTree)
{
  std::string name;
  std::string  nameFirst;
  std::string  nameSecond;
  std:: cin >> name >> nameFirst >> nameSecond;
  Tree< size_t, std::string > newTree;
  Tree< size_t, std::string > firstDictionary = allTree.at(nameFirst);
  Tree< size_t, std::string > secondDictionary = allTree.at(nameSecond);
  Tree< size_t, std::string >::Iterator iteratorFirst = firstDictionary.begin();
  Tree< size_t, std::string >::Iterator endFirst = firstDictionary.end();
  Tree< size_t, std::string >::Iterator iteratorSecond = secondDictionary.begin();
  Tree< size_t, std::string >::Iterator endSecond = secondDictionary.end();
  while(iteratorFirst != endFirst)
  {
    std::pair< size_t, std::string > pair = *iteratorFirst;
    newTree.insert(pair);
    iteratorFirst++;
  }
  while(iteratorSecond != endSecond)
  {
    std::pair< size_t, std::string > pair = *iteratorSecond;
    if(firstDictionary.find(pair.first) == endFirst)
    {
      newTree.insert(pair);
    }
    iteratorSecond++;
  }
  allTree.insert(name, newTree);
}

void kovshikov::outText(std::ostream& out, std::string string)
{
  out << string << "\n";
}
