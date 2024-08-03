#ifndef ADDITIONALFUNCTIONS_HPP
#define ADDITIONALFUNCTIONS_HPP
#include "MaineArray.hpp"

namespace kaseev
{
  using ULL_ListPair = std::pair< std::string, kaseev::List< unsigned long long > >;
  using IntListPair = std::pair< std::string, List< int > >;
  void readList(const std::string &line, kaseev::List< ULL_ListPair >& arr, bool &marker);
  unsigned long long sumNumbersInString(const std::string& line);
  void sumNumbersInArray(const kaseev::List< IntListPair >& sums, bool &marker);
  void printListNames(const kaseev::List< ULL_ListPair >& arr);
  kaseev::List< IntListPair > calculateSumList(const kaseev::List< ULL_ListPair >& arr);
  unsigned long long convertToULL(const std::string &str, bool &NoNumbers) noexcept;
}

#endif
