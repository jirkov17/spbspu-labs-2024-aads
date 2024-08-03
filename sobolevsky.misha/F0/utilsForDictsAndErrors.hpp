#ifndef UTILSFORDICTSANDERRORS_HPP
#define UTILSFORDICTSANDERRORS_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include "myList.hpp"
#include "myMultiMap.hpp"

using mypair = std::pair< std::string, sobolevsky::MyMultiMap< size_t, std::string > >;

namespace sobolevsky
{
  void error(std::ostream & out);
  void errorInpName(std::ostream & out);
  bool isNameHere(mypair &pair, const std::string &name);
  void dictOutput(mypair &myPair, std::ostream & out, size_t n, bool mode);
  char charCheck(char in);
  typename List< mypair >::Iterator findIf(typename List< mypair >::Iterator &&first, typename List< mypair >::Iterator &&last,
  std::string &name);
}

#endif
