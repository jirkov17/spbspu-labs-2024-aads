#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <string>
#include <AvlTree.hpp>

namespace nikiforov
{
  using dictionariesTree = AvlTree< std::string, AvlTree< int, std::string > >;

  std::string cutElem(std::string& str);

  void createDictionary(std::string& strVocab, AvlTree< int, std::string >& dict);

  void print(dictionariesTree& dictionaries, std::istream& in, std::ostream& out);

  void complement(dictionariesTree& dictionaries, std::istream& in, std::ostream& out);

  void intersect(dictionariesTree& dictionaries, std::istream& in, std::ostream& out);

  void unite(dictionariesTree& dictionaries, std::istream& in, std::ostream& out);

  std::ostream& errorMessage(std::ostream& out);

  std::ostream& emptyMessage(std::ostream& out);
}

#endif
