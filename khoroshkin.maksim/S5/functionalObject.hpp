#ifndef FUNCTIONALOBJECT_HPP
#define FUNCTIONALOBJECT_HPP

#include <utility>
#include <numeric>
#include <queue.hpp>

namespace khoroshkin
{
  struct Traverse
  {
    void operator()(const std::pair< const int, std::string > & kv_pair)
    {
      if (result > std::numeric_limits< int >::max() - kv_pair.first)
      {
        throw std::overflow_error("Error: overflow!\n");
      }
      if (kv_pair.first < 0 && result < std::numeric_limits< int >::min() - kv_pair.first)
      {
        throw std::underflow_error("Error: underflow!\n");
      }
      result += kv_pair.first;
      bypass.push(kv_pair.second);
    }
    Queue< std::string > bypass{};
    int result = 0;
  };
}

#endif
