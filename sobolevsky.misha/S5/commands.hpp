#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <string>
#include <tree.hpp>

namespace sobolevsky
{
  void ascending(std::ostream &out, const sobolevsky::AVLtree< long long, std::string, long long > &tree);
  void descending(std::ostream &out, const sobolevsky::AVLtree< long long, std::string, long long > &tree);
  void breadth(std::ostream &out, const sobolevsky::AVLtree< long long, std::string, long long > &tree);
}

#endif
