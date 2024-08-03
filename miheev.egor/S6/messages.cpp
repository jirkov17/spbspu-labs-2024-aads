#include "messages.hpp"

void miheev::messages::sendWrongAmountOfArgs(std::ostream& out)
{
  out << "wrong amount of parameters";
}

void miheev::messages::sendInvalidConversion(std::ostream& out)
{
  out << "can't convert size_argument to number";
}

void miheev::messages::sendInapropriateParameter(std::ostream& out)
{
  out << "inapropriate value of parameter [size]";
}

void miheev::messages::sendInvalidSecondArgument(std::ostream& out)
{
  out << "Invalid second argument";
}

void miheev::messages::sendInvalidFirstArgument(std::ostream& out)
{
  out << "Invalid first argument";
}
