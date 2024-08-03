#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "IOProcessing.hpp"

namespace miheev
{
  namespace commands
  {
    using Command = std::function< void(std::istream&, std::ostream&, Datasets&) >;
    void print(std::istream&, std::ostream&, const Datasets&);
    void complement(std::istream&, std::ostream&, Datasets&);
    void intersect(std::istream&, std::ostream&, Datasets&);
    void unite(std::istream&, std::ostream&, Datasets&);
  }
}

#endif
