#include "ErrorMessage.hpp"
#include <iostream>

namespace sukacheva
{
  void ErrorMessage(std::ostream& out)
  {
    out << "<INVALID COMMAND>\n";
  }

  void EmptyMessage(std::ostream& out)
  {
    out << "<EMPTY>\n";
  }
}
