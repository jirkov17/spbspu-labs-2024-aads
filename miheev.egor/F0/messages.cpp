#include "messages.hpp"

void miheev::messages::sendInvalidCommand(std::ostream& out)
{
  out << "invalid command";
}

void miheev::messages::sendGoodbye(std::ostream& out)
{
  out << "Goodbye!";
}
