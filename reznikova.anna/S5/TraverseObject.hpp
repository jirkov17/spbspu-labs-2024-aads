#ifndef TRAVERSEOBJECT_HPP
#define TRAVERSEOBJECT_HPP

#include <utility>
#include <limits>
#include <Queue.hpp>

namespace reznikova
{
  struct Traverse
  {
    void operator()(const std::pair< int, std::string > & pair_type)
    {
      int max = std::numeric_limits< int >::max();
      int min = std::numeric_limits< int >::min();
      if (result > max - pair_type.first)
      {
        throw std::runtime_error("Overflow\n");
      }
      if (pair_type.first < 0 and result < min - pair_type.first)
      {
        throw std::runtime_error("Underflow\n");
      }
      result += pair_type.first;
      values.push(pair_type.second);
    }
    Queue< std::string > values;
    int result = 0;
  };
}

#endif
