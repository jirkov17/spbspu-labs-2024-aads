#include "mainExtension.hpp"

#include <iostream>
#include <list.hpp>

void anikanov::printUsingError(std::ostream &os)
{
  os << "Usage: [ascending|descending] [ints|floats] [size]" << std::endl;
}

void anikanov::printInvalidCount(std::ostream &os)
{
  os << "Size must be bigger then 0!\n";
}

void anikanov::printInvalidType(std::ostream &os)
{
  os << "Invalid type! Use ints or floats\n";
}
