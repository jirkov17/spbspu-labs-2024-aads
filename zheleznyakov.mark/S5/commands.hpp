#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include <tree.hpp>
#include "datatypes.hpp"

namespace zheleznyakov
{
  namespace commands
  {
    void ascending(std::ostream &, const data_t &);
    void descending(std::ostream &, const data_t &);
    void breadth(std::ostream &, const data_t &);
  }

  void outInvalidCommand(std::ostream &);
  void outEmpty(std::ostream &);
}
#endif
