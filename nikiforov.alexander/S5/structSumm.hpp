#ifndef STRUCTSUMM_HPP
#define STRUCTSUMM_HPP
#include <string>
#include <limits>
#include <ios>

namespace nikiforov
{
  struct Key_summ {
    void operator()(const std::pair< const long long, std::string >& key_value)
    {
      bool lowerOverflow = (key_value.first < 0 && result < (std::numeric_limits< long long >::min() - key_value.first));
      bool upperOverflow = (key_value.first > 0 && result > (std::numeric_limits< long long >::max() - key_value.first));

      if (upperOverflow || lowerOverflow)
      {
        throw std::out_of_range("Error: Overflow!");
      }
      result += key_value.first;
      strValues += (" " + key_value.second);
    }
    long long result = 0;
    std::string strValues = "";
  };
}

#endif
