#ifndef DICT_HPP
#define DICT_HPP
#include <string>
#include <vector>
#include <tree.hpp>
#include <list.hpp>

namespace zheleznyakov
{
  using wordcoord_t = std::pair< size_t, size_t >;
  using wordpair_t = List< wordcoord_t >;
  using wordpairs_t = Tree< std::string, wordpair_t >;

  size_t getWordsCount(std::string);
  size_t getLinesCount(std::string);

  wordpairs_t getDict(const std::string &);
  bool isPunctuationMark(const char c);
}
#endif
