#include "IOFunctions.hpp"

void miheev::readTree(std::istream& in, tree_t& container)
{
  long long tempKey = 0;
  std::string tempValue = "";
  while (!in.eof())
  {
    in >> tempKey >> tempValue;
    if (in.fail())
    {
      return;
    }
    container.insert(tempKey, tempValue);
  }
}

void miheev::sendEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}
