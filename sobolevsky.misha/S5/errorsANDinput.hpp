#ifndef ERRORSANDINPUT_HPP
#define ERRORSANDINPUT_HPP

#include <tree.hpp>

namespace sobolevsky
{
  void inputFromFile(std::istream &in, sobolevsky::AVLtree< long long, std::string, long long > &data);
  void errorEmpty(std::ostream &out);
  void errorOverflowOrOutOfRange(std::ostream &out);
}

#endif
