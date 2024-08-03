#ifndef MESSAGES_HPP
#define MESSAGES_HPP

#include <iostream>

namespace miheev
{
  namespace messages
  {
    void sendWrongAmountOfArgs(std::ostream&);
    void sendInvalidConversion(std::ostream&);
    void sendInapropriateParameter(std::ostream&);
    void sendInvalidSecondArgument(std::ostream&);
    void sendInvalidFirstArgument(std::ostream&);
  }
  template< typename Printer, typename... Args >
  void errorWrapper(std::ostream&, Printer p, Args... args);
}

template< typename Printer, typename... Args >
void miheev::errorWrapper(std::ostream& out, Printer p, Args... args)
{
  out << "[ERROR]: ";
  p(out, args...);
  out << '\n';
}

#endif
