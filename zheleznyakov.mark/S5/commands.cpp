#include "commands.hpp"
#include "keyValueSum.hpp"
#include <string>

void zheleznyakov::commands::ascending(std::ostream & out, const data_t & data)
{
  KeyValueSum kvSum;
  kvSum = data.ctraverseLnR(kvSum);
  out << kvSum.getKeySum() << kvSum.getValueSum() << '\n';
}

void zheleznyakov::commands::descending(std::ostream & out, const data_t & data)
{
  KeyValueSum kvSum;
  kvSum = data.ctraverseRnL(kvSum);
  out << kvSum.getKeySum() << kvSum.getValueSum() << '\n';
}

void zheleznyakov::commands::breadth(std::ostream & out, const data_t & data)
{
  KeyValueSum kvSum;
  kvSum = data.ctraverseBreadth(kvSum);
  out << kvSum.getKeySum() << kvSum.getValueSum() << '\n';
}

void zheleznyakov::outInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>\n";
}

void zheleznyakov::outEmpty(std::ostream & out)
{
  out << "<EMPTY>\n";
}
