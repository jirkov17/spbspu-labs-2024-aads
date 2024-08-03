#ifndef KEY_VAL_SUMM_HPP
#define KEY_VAL_SUMM_HPP
#include <string>

namespace doroshenko
{
  struct KeyValSumm
  {
    KeyValSumm();
    void operator()(const std::pair< const int, std::string >& keyval);
    int keySum_;
    std::string valSum_;
  };
}

#endif
