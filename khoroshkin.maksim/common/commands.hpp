#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <string>
#include "tree.hpp"

namespace khoroshkin
{
  std::string getString(std::string & line, size_t & pos);
  long long getKey(std::string & line, size_t & pos);
  void print(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree);
  void complement(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree);
  void intersect(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree);
  void unite(khoroshkin::Tree< std::string, khoroshkin::Tree< long long, std::string > > & Tree);
  void outMessage(std::ostream & out, const std::string & message);
}

#endif
