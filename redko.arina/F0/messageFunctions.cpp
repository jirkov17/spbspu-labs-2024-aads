#include "messageFunctions.hpp"

void redko::printInvalidMessage(std::ostream & out)
{
  out << "<invalid command>\n";
}

void redko::printInvalidFile(std::ostream & out)
{
  out << "<unable to open the file>\n";
}

void redko::printInvalidFormat(std::ostream & out)
{
  out << "<invalid Huffman format>\n";
}

void redko::printEmptyInput(std::ostream & out)
{
  out << "<empty input>\n";
}
