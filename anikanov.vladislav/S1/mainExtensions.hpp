#ifndef MAINEXTENSIONS_HPP
#define MAINEXTENSIONS_HPP

#include <iomanip>
#include <list.hpp>

namespace anikanov {
  using list = List< unsigned long long >;
  using mainList = List< std::pair< std::string, list > >;
  using getSums = std::pair< list, bool >;

  List< std::string > split(const std::string &str);
  void inputList(std::unique_ptr< mainList > &lists, std::istream &stream);
  bool printNames(const std::unique_ptr< mainList > &lists, std::ostream &cout);
  getSums countList(const std::unique_ptr< mainList > &lists, std::ostream &cout);
  void printList(const list &list, std::ostream &cout);
}
#endif
