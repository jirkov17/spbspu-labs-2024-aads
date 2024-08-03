#include "utils.hpp"

std::ostream& psarev::outWrongParams(std::ostream& out)
{
  out << "Error: Wrong input parameters!\n";
  return out;
}

std::ostream& psarev::outWrongSize(std::ostream& out)
{
  out << "Error: Wrong size! It must be positive!\n";
  return out;
}
