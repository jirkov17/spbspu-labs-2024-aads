#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iosfwd>
#include <string>
#include "BinarySearchTree.hpp"

namespace doroshenko
{
  using dictionary = BST< std::string, std::string >;
  void help(std::ostream& output);
  void createDict(BST< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void removeDict(BST< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void printDict(const BST< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void sortDict(BST< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void sortByFrequency(BST< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void sortByAlphabet(BST< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void deleteKey(dictionary& dict, std::istream& input, std::ostream& output);
  void findKey(dictionary& dict, std::istream& input, std::ostream& output);
  void openFile(dictionary& dict, std::istream& input, std::ostream& output);
  void writeToFile(const BST< std::string, dictionary >& dicts, std::istream& input, std::ostream& output);
  void printTop(BST< std::string, dictionary >& dicts, std::istream& in, std::ostream& out);
  void warningDict(std::ostream& output);
  void warningElem(std::ostream& output);
  void warningFile(std::ostream& output);
  void warningInvCom(std::ostream& output);
}

#endif
