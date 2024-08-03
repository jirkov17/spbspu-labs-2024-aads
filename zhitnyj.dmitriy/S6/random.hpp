#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <list>
#include <algorithm>
#include <functional>
#include <deque>
#include <List.hpp>

namespace zhitnyj {
  int generateRandomInt(int min, int max);
  float generateRandomFloat(float min, float max);
  template< typename T >
  void generateNumbers(zhitnyj::List< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, size_t size, bool isInt);
}

int zhitnyj::generateRandomInt(int min, int max) {
  return min + std::rand() % (max - min + 1);
}

float zhitnyj::generateRandomFloat(float min, float max) {
  return min + static_cast< float >(std::rand()) / static_cast< float >(RAND_MAX) * (max - min);
}

template< typename T >
void zhitnyj::generateNumbers(zhitnyj::List< T > &singleList, std::list< T > &doubleList, std::deque< T > &deq, size_t size, bool isInt) {
  for (size_t i = 0; i < size; ++i) {
    if (isInt) {
      int num = generateRandomInt(0, 100);
      singleList.push_back(num);
      doubleList.push_back(num);
      deq.push_back(num);
    }
    else {
      float num = generateRandomFloat(0.0f, 100.0f);
      singleList.push_back(num);
      doubleList.push_back(num);
      deq.push_back(num);
    }
  }
}

#endif
