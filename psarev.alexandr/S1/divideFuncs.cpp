#include "divideFuncs.hpp"

std::string psarev::getOrd(std::string& line)
{
  std::string ord;
  ord = line.substr(0, line.find_first_of(" ", 0));
  if (line.find_first_of(" ") != std::string::npos)
  {
    line = line.substr(line.find_first_of(" ") + 1);
  }
  else
  {
    line = "";
  }
  return ord;
}

unsigned long long psarev::getDigit(std::string& line)
{
  unsigned long long digit = std::stoull(line.substr(0, line.find_first_of(" ", 0)));
  if (line.find_first_of(" ") != std::string::npos)
  {
    line = line.substr(line.find_first_of(" ") + 1);
  }
  else
  {
    line = "";
  }
  return digit;
}
