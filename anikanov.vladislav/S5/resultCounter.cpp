#include "resultCounter.hpp"
#include <limits>
#include <stdexcept>
#include <queue.hpp>

#include <iostream>

anikanov::ResultCounter::ResultCounter()
  : result(0)
{
}

void anikanov::ResultCounter::operator()(const std::pair< long long, std::string > &key_value)
{
  bool isOverflow = (key_value.first > 0) && result > std::numeric_limits< long long >::max() - key_value.first;
  bool isUndeflow = (key_value.first < 0) && (result < std::numeric_limits< long long >::min() - key_value.first);

  if (isOverflow) {
    throw std::overflow_error("Key sum overflow!");
  } else if (isUndeflow) {
    throw std::underflow_error("Key sum undeflow!");
  }
  result += key_value.first;
  values.push(key_value.second);
}

long long anikanov::ResultCounter::getResult() const
{
  return result;
}

std::string anikanov::ResultCounter::getValues() const
{
  std::string ans;
  Queue< std::string > tempQueue = values;
  while (!tempQueue.isEmpty()) {
    ans += tempQueue.front();
    tempQueue.pop();
    if (!tempQueue.isEmpty()) {
      ans += " ";
    }
  }
  return ans;
}

anikanov::ResultCounter anikanov::ResultCounter::operator=(const anikanov::ResultCounter &rhs) noexcept
{
  if (this == &rhs) {
    return *this;
  }
  result = rhs.result;
  values = rhs.values;
  return *this;
}

anikanov::ResultCounter::ResultCounter(anikanov::ResultCounter &lhs)
{
  result = lhs.result;
  values = std::move(lhs.values);
}
