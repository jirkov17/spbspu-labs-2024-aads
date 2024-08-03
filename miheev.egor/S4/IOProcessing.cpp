#include "IOProcessing.hpp"

std::string miheev::getWord(std::string& s)
{
  std::string symbol = s.substr(0, s.find(" "));
  if (s.find(" ") == std::string::npos)
  {
    s = "";
  }
  else
  {
    s = s.substr(s.find(" ") + 1);
  }
  return symbol;
}

void miheev::inputData(std::string& line, miheev::Data& container)
{
  int key = 0;
  std::string value = "";
  while (line != "")
  {
    key = std::stoi(getWord(line));
    value = getWord(line);
    container.insert(key, value);
  }
}

void miheev::inputDatasets(std::istream& in, miheev::Tree< std::string, miheev::Data >& container)
{
  std::string line = "";
  getline(in, line);
  std::string datasetName = getWord(line);
  if (datasetName == "")
  {
    return;
  }
  miheev::Data datasetData;
  inputData(line, datasetData);
  container.insert(datasetName, datasetData);
}

void miheev::sendInvalidCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

void miheev::sendEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}
