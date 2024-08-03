#include "cutFunctions.hpp"
#include <string>

std::string ponomarev::getName(std::string & line)
{
  std::string name = line.substr(0, line.find(" "));
  if (line.find(" ") == std::string::npos)
  {
    line = "";
  }
  else
  {
    line = line.substr(line.find(" ") + 1);
  }
  return name;
}

unsigned long long ponomarev::getNumber(std::string & line)
{
  unsigned long long num = std::stoull(line.substr(0, line.find(" ")));
  if (line.find(" ") == std::string::npos)
  {
    line = "";
  }
  else
  {
    line = line.substr(line.find(" ") + 1);
  }
  return num;
}
