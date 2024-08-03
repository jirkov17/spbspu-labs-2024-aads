#include "details.hpp"

std::ostream &mihalchenko::printWrongInput(std::ostream &out)
{
    out << "ERROR: wrong input\n";
    return out;
}

std::ostream& mihalchenko::printWrongSize(std::ostream& out)
{
  out << "ERROR: wrong size\n";
  return out;
}
