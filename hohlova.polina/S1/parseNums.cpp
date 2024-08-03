#include "parseNums.hpp"

unsigned long long hohlova::ParseNum(const std::string& str, size_t& pos)
{
  auto symbol = static_cast< unsigned char >(str[pos]);
  unsigned long long result = 0;
  while (std::isdigit(symbol))
  {
    result = result * 10 + (symbol - '0');
    if (pos == str.size() - 1)
    {
      ++pos;
      break;
    }
    symbol = static_cast< unsigned char >(str[++pos]);
  }
  return result;
}

template< typename T >
std::ostream& hohlova::operator<<(std::ostream& os, const hohlova::List< T >& list)
{
  std::vector<std::string> names;
  std::vector< std::vector< unsigned long long > > values;

  for (auto it = list.begin(); it != list.end(); ++it)
  {
    names.push_back((*it).first);
    values.push_back((*it).second);
  }

  size_t max_size = 0;
  for (const auto& v : values)
  {
    max_size = std::max(max_size, v.size());
  }
  for (size_t i = 0; i < max_size; ++i)
  {
    for (size_t j = 0; j < names.size(); ++j)
    {
      if (i < values[j].size())
      {
        os << values[j][i];
      }
      if ((j + 1 < names.size()) && (i < values[j + 1].size()) && (i + 1 < max_size))
      {
        os << " ";
      }
    }
    os << "\n";
  }
  return os;
}
