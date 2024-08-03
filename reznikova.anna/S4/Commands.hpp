#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <fstream>
#include "Tree.hpp"

namespace reznikova
{
  void outputInvalidCommand(std::ostream & out);
  void outputEmptyError(std::ostream & out);
  std::string getValue(std::string & input, size_t & i);
  size_t getKey(std::string & input, size_t & i);
  void readFromFile(std::ifstream & is, Tree< std::string, Tree< size_t, std::string > > & treeMap);
  void printCommand(Tree< std::string, Tree< size_t, std::string > > & treeMap);
  void complementCommand(Tree< std::string, Tree< size_t, std::string > > & treeMap);
  void intersectCommand(Tree< std::string, Tree< size_t, std::string > > & treeMap);
  void unionCommand(Tree< std::string, Tree< size_t, std::string > > & treeMap);
}
#endif
