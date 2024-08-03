#include "errorsANDinput.hpp"

void sobolevsky::inputFromFile(std::istream &file, sobolevsky::AVLtree< long long, std::string, long long > &data)
{
  while (!file.eof())
  {
    if (file.fail())
    {
      file.clear();
    }
    long long key;
    std::string value;
    if (file >> key >> value)
    {
      data.insert(std::make_pair(key, value));
    }
  }
}

void sobolevsky::errorEmpty(std::ostream &out)
{
  out << "<EMPTY>\n";
}

void sobolevsky::errorOverflowOrOutOfRange(std::ostream &out)
{
  out << "<OVERLFOW / OUT OF RANGE>\n";
}
