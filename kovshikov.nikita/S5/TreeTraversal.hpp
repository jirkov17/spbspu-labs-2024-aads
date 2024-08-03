#ifndef STRUCTSUMMA_HPP
#define STRUCTSUMMA_CPP
#include <utility>
#include <limits>
#include "queue.hpp"

namespace kovshikov
{
  struct TreeTraversal
  {
    void operator()(const std::pair< const int, std::string >& element)
    {
      int max = std::numeric_limits< int >::max();
      int min = std::numeric_limits< int >::min();
      if(element.first > 0 && max - element.first < result)
      {
        throw std::overflow_error("<SUMMA OVERFLOWED>");
      }
      else if(element.first < 0 && min - element.first > result)
      {
        throw std::underflow_error("<SUMMA UNDERFLOWED>");
      }
      result += element.first;
      allValue.push(element.second);
    }
    Queue< std::string > allValue;
    int result = 0;
  };
}

#endif
