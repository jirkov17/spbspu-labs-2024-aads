#ifndef FUNC_OBJ_HPP
#define FUNC_OBJ_HPP

#include <string>

namespace ponomarev
{
  struct Key_summ
  {
    void operator()(const std::pair< long long, std::string > & value);

    int sum_ = 0;
    std::string valueRes_;
  };
}

#endif
