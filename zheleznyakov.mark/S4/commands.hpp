#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <istream>
#include "datatypes.hpp"
#include <tree.hpp>

namespace zheleznyakov
{
  namespace commands
  {
    void print(std::istream &, std::ostream &, const dicts_t &);
    void complement(std::istream & in, std::ostream & out, dicts_t & dicts);
    void intersect(std::istream & in, std::ostream & out, dicts_t & dicts);
    void append(std::istream & in, std::ostream & out, dicts_t & dicts);
  }

  void outInvalidCommand(std::ostream &);
  void outEmpty(std::ostream &);
}
#endif
