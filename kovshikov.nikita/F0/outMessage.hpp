#ifndef OUTMESSAGE_HPP
#define OUTMESSAGE_HPP
#include <iosfwd>
#include <string>

namespace kovshikov
{
  void outDescription(std::ostream& out);
  void outMessage(std::string message, std::ostream& out);
}

#endif
