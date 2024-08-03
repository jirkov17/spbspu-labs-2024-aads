#ifndef MESSAGEFUNCTIONS_HPP
#define MESSAGEFUNCTIONS_HPP
#include <ostream>

namespace redko
{
  void printInvalidMessage(std::ostream & out);
  void printInvalidFile(std::ostream & out);
  void printInvalidFormat(std::ostream & out);
  void printEmptyInput(std::ostream & out);
}

#endif
