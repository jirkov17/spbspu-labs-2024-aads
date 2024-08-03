#ifndef IO_FUNCTIONS_HPP
#define IO_FUNCTIONS_HPP

#include <iosfwd>
#include "binarySearchTreeAVL.hpp"

namespace ponomarev
{
  void inputFromFile(std::istream & in, BSTree< std::string, BSTree< int, std::string, int >, int > & data);
  std::ostream & printInvalidCommandMessage(std::ostream & out);
  std::ostream & printEmptyDataset(std::ostream & out);
}

#endif
