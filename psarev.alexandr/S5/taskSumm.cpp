#include "taskSumm.hpp"
#include <limits>
#include <stdexcept>

psarev::TaskSumm::TaskSumm() :
  keySumm(0),
  valSumm("")
{}

void psarev::TaskSumm::operator()(const std::pair< const long long, std::string >& dataPair)
{
  long long llMax = std::numeric_limits< long long >::max();
  bool overCheck = (keySumm > 0) && (dataPair.first > 0) && (llMax - keySumm < dataPair.first);

  if (overCheck)
  {
    throw std::overflow_error("<OVERFLOW ERROR>");
  }

  long long llMin = std::numeric_limits< long long >::min();
  bool underCheck = (keySumm < 0) && (dataPair.first < 0) && (llMin - keySumm > dataPair.first);
  if (underCheck)
  {
    throw std::underflow_error("<UNDERFLOW ERROR>");
  }

  keySumm += dataPair.first;

  valSumm += ( " " + dataPair.second);
}

long long psarev::TaskSumm::getKeySumm()
{
  return keySumm;
}

std::string psarev::TaskSumm::getValSumm()
{
  return valSumm;
}
