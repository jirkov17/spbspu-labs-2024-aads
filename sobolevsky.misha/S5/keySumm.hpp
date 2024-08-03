#ifndef KEYSUMM_HPP
#define KEYSUMM_HPP

#include <utility>
#include <string>
#include <limits>
#include <stdexcept>

namespace sobolevsky
{
  struct Key_summ
  {
  public:
    Key_summ();

    void operator()(const std::pair< const long long, std::string > &key_value);

    long long getKeyResult();
    std::string getValueResult();
  private:
    long long keyResult_;
    std::string valueResult_;
  };
}

#endif
