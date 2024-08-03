#ifndef KEY_SUMM_HPP
#define KEY_SUMM_HPP

#include <utility>
#include <string>

namespace miheev
{
  struct KeySumm
  {
  public:
    KeySumm();
    ~KeySumm() = default;
    void operator()(const std::pair< const long long, std::string >& keyValue);
    std::string getResults();
  private:
    long long result;
    std::string values;
  };
}

#endif
