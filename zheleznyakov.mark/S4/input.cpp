#include "input.hpp"
#include <iostream>
#include <string>

std::string zheleznyakov::extractFirstWord(std::string & str)
{
  size_t pos = str.find(' ');
  if (pos == std::string::npos)
  {
    std::string firstWord = str;
    str.clear();
    return firstWord;
  }
  std::string firstWord = str.substr(0, pos);
  str = str.substr(pos + 1);
  return firstWord;
}

void zheleznyakov::readDictContents(std::string line, dict_t & dict)
{
  while (!line.empty())
  {
    int key = std::stoi(extractFirstWord(line));
    std::string value = extractFirstWord(line);
    dict.insert(key, value);
  }
}

void zheleznyakov::readDict(std::string line, dicts_t & dicts)
{
  std::string currentTitle = extractFirstWord(line);
  if (currentTitle == "")
  {
    return;
  }
  dict_t currentDict;
  readDictContents(line, currentDict);
  dicts.insert(currentTitle, currentDict);
}
