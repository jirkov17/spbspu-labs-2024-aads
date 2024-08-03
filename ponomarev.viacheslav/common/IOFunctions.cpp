#include "IOFunctions.hpp"
#include <iostream>
#include "cutFunctions.hpp"

void ponomarev::inputFromFile(std::istream & in, BSTree< std::string, BSTree< int, std::string, int >, int > & data)
{
  std::string dataLine = "";
  std::string name = "";
  std::string value = "";
  int key = 0;
  using data_t = ponomarev::BSTree< int, std::string, int >;

  while (std::getline(in, dataLine))
  {
    data_t dataSet;
    name = ponomarev::getName(dataLine);
    while (!dataLine.empty())
    {
      key = int(ponomarev::getNumber(dataLine));
      value = ponomarev::getName(dataLine);
      dataSet.insert(std::make_pair(key, value));
    }
    data.insert(std::make_pair(name, dataSet));
  }
}

std::ostream & ponomarev::printInvalidCommandMessage(std::ostream & out)
{
  out << "<INVALID COMMAND>" << "\n";
  return out;
}

std::ostream & ponomarev::printEmptyDataset(std::ostream & out)
{
  out << "<EMPTY>" << "\n";
  return out;
}
