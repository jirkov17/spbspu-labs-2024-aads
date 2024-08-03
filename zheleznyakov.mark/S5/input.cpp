#include "input.hpp"

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

void zheleznyakov::readData(std::string line, data_t & data)
{
  while (!line.empty())
  {
    long long key = std::stoll(extractFirstWord(line));
    std::string value = extractFirstWord(line);
    data.insert(key, value);
  }
}
