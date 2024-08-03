#ifndef KEYSUM_HPP
#define KEYSUM_HPP

#include <limits>
#include <stdexcept>
#include <Queue.hpp>

namespace zhitnyj {
  struct KeySum {
    void operator()(const std::pair< const long long, std::string > &key_value) {
      queue.push(key_value);
      bool isOverflow = result_ > std::numeric_limits< long long >::max() - key_value.first;
      bool isUndeflow = (key_value.first < 0) && (result_ < std::numeric_limits< long long >::min() - key_value.first);

      if (isOverflow) {
        throw std::overflow_error("Key sum overflow!");
      }
      else if (isUndeflow) {
        throw std::overflow_error("Key sum undeflow!");
      }
      result_ += key_value.first;
    }

    long long result_ = 0;
    Queue <std::pair< const long long, std::string>> queue;
  };
}

#endif
