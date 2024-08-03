#ifndef DICTIONARYCOMMANDS_HPP
#define DICTIONARYCOMMANDS_HPP
#include <iomanip>
#include <map>
#include <algorithm>
#include <iostream>
#include <string>
#include <commands.hpp>

namespace nikiforov
{
  using mapDictionaries_t = nikiforov::AvlTree< std::string, nikiforov::AvlTree< std::string, size_t > >;
  using invertedMap_t = std::multimap< size_t, std::string >;
  using AvlTreeConstIter = nikiforov::AvlTree< std::string, size_t >::ConstIterator;

  void printCommands(std::ostream& out);

  std::string cutNameFile(std::string& str);

  void createDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string mkdir);
  void getDictionary(nikiforov::AvlTree< std::string, size_t >& dictionary, std::istream& in);
  void deleteDelimeters(std::string& str);
  bool checkAlpha(std::string& str);

  void open(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void deleteDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void printNamesDictionaries(const mapDictionaries_t& mapDictionaries, std::ostream& out);

  void add(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void unit(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void rename(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void clear(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void save(const mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out);

  void writingDictionaries(const mapDictionaries_t& mapDictionaries, std::string nameMkdir, std::ofstream& fout);

  void printWordAndFrequency(AvlTreeConstIter begin, AvlTreeConstIter end, std::ostream& out);
  void printWordAndFrequency(nikiforov::AvlTree< std::string, size_t >::Iterator iterPair, std::ostream& out);

  void select(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string& nameSelectedDictionary);
  void printDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string nameSelectedDictionary);
  void printMost(nikiforov::AvlTree< std::string, size_t >& invertedDictionary, std::istream& in, std::ostream& out);
  void find(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string nameSelectedDictionary);
  void erase(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string nameSelectedDictionary);

}
#endif
