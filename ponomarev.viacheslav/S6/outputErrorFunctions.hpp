#ifndef OUTPUT_ERROR_FUNCTIONS_HPP
#define OUTPUT_ERROR_FUNCTIONS_HPP

#include <iosfwd>

namespace ponomarev
{
  std::ostream & printInvalidParameters(std::ostream & out);
  std::ostream & pringWrongSize(std::ostream & out);
}

#endif
