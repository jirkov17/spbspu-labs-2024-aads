#include "KeyValSumm.hpp"
#include <limits>
#include <stdexcept>

doroshenko::KeyValSumm::KeyValSumm() :
  keySum_(0),
  valSum_("")
{};

void doroshenko::KeyValSumm::operator()(const std::pair< const int, std::string >& keyval)
{
  int maximum = std::numeric_limits< int >::max();
  int minimum = std::numeric_limits< int >::min();
  if (maximum - keyval.first < keySum_ || (keyval.first < 0 && minimum - keyval.first > keySum_))
  {
    throw std::out_of_range("<OUT OF RANGE>\n");
  }
  keySum_ += keyval.first;
  if (!valSum_.empty())
  {
    valSum_ += " ";
  }
  valSum_ += keyval.second;
}
