#include "keySumm.hpp"
#include <limits>
#include <stdexcept>

miheev::KeySumm::KeySumm():
  result(0),
  values("")
{}

void miheev::KeySumm::operator()(const std::pair< const long long, std::string >& keyValue)
{
  bool overflowIsPossible = result > 0 && keyValue.first > 0;
  bool overflow = std::numeric_limits< long long >::max() - result < keyValue.first;
  if (overflowIsPossible && overflow)
  {
    throw std::overflow_error("calculating sum of case encounter overflow");
  }
  bool underflowIsPossbile = result < 0 && keyValue.first < 0;
  bool underflow = std::numeric_limits< long long >::min() - result > keyValue.first;
  if (underflowIsPossbile && underflow)
  {
    throw std::underflow_error("calculating sum of case encounter underflow");
  }
  result += keyValue.first;
  if (!values.empty())
  {
    values += " ";
  }
  values += keyValue.second;
}

std::string miheev::KeySumm::getResults()
{
  return std::to_string(result) + " " + values;
}
