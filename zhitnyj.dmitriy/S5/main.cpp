#include <iostream>
#include <functional>
#include <limits>
#include <fstream>
#include <BinarySearchTree.hpp>
#include "TreeTraversal.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cerr << "Wrong input\n";
    return 1;
  }

  zhitnyj::BSTree< long long, std::string > dictionaries;
  zhitnyj::BSTree< std::string, std::function< void(zhitnyj::BSTree< long long, std::string > &) > > cmds;

  cmds.insert(std::make_pair("ascending", zhitnyj::traverseAscending));
  cmds.insert(std::make_pair("descending", zhitnyj::traverseDescending));
  cmds.insert(std::make_pair("breadth", zhitnyj::traverseBreadth));

  try {
    std::ifstream file(argv[2]);
    if (!file) {
      throw std::runtime_error("Unable to open file");
    }

    long long key;
    std::string value;
    while (file >> key >> value) {
      dictionaries.push(key, value);
    }
  } catch (const std::exception &e) {
    std::cerr << "Error loading file: " << e.what() << "\n";
    return 1;
  }

  try {
    std::string command = argv[1];
    auto commandIter = cmds.find(command);
    if (commandIter != cmds.end() && !command.empty()) {
      commandIter->second(dictionaries);
    }
    else if (!command.empty()) {
      zhitnyj::invalidCommandError(std::cerr);
      return 1;
    }
  } catch (const std::overflow_error &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
