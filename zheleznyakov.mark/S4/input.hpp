#ifndef INPUT_HPP
#define INPUT_HPP
#include <string>
#include "datatypes.hpp"

namespace zheleznyakov
{
  std::string extractFirstWord(std::string & str);
  void readDict(std::string, dicts_t &);
  void readDictContents(std::string, dict_t &);
}
#endif
