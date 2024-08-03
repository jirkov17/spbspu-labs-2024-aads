#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <Tree.hpp>

namespace reznikova
{
  void ascendingCommand(Tree< int, std::string > & tree);
  void descendingCommand(Tree< int, std::string > & tree);
  void breadthCommand(Tree< int, std::string > & tree);
}

#endif
