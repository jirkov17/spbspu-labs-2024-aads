#include "outputErrorFunctions.hpp"
#include <iostream>

std::ostream & ponomarev::printInvalidParameters(std::ostream & out)
{
  out << "wrong number of parameters\n";
  return out;
}

std::ostream & ponomarev::pringWrongSize(std::ostream & out)
{
  out << "wrong size parameter\n";
  return out;
}
