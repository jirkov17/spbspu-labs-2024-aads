#ifndef IO_PROCESSGIN_HPP
#define IO_PROCESSGIN_HPP

#include <string>
#include <utility>
#include "tree.hpp"

namespace miheev
{
  using Data = Tree< int, std::string >;
  using Datasets = Tree< std::string, Data >;
  std::string getWord(std::string&);
  void inputData(std::string&, Data&);
  void inputDatasets(std::istream&, Datasets&);
  void sendInvalidCommand(std::ostream&);
  void sendEmpty(std::ostream&);
}

#endif
