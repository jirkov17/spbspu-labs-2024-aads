#ifndef COMMANDS_HPP
#define COMMANDS_HPP

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
  void getCommands(std::istream & in, std::ostream & out);
  void getLoadAndCreate(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in);
  void getDelete(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in);
  void getAllDicts(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in, std::ostream & out);
  void getSelect(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in, std::ostream & out);
  void holyTrinity(mypair &myPair, std::istream & in, std::ostream & out);
  void printDict(mypair &myPair, std::istream & in, std::ostream & out);
  void uniqeWords(mypair &myPair, std::istream & in, std::ostream & out);
  void wordCount(mypair &myPair, std::istream & in, std::ostream & out);
  void getRename(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in);
  void save(mypair &myPair, std::istream & in);
  void getCompareDicts(std::shared_ptr< sobolevsky::List< mypair > > myVec, std::istream & in, std::ostream & out);
}

#endif
