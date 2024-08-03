#include <iostream>
#include <functional>
#include <limits>
#include "BinarySearchTree.hpp"
#include "CommandProcessor.hpp"

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Wrong input\n";
    return 1;
  }

  zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > dictionaries;
  zhitnyj::BSTree< std::string, std::function< void(zhitnyj::BSTree< std::string, zhitnyj::BSTree< long long, std::string > > &) > > cmds;

  cmds.insert(std::make_pair("print", zhitnyj::handlePrint));
  cmds.insert(std::make_pair("complement", zhitnyj::handleComplement));
  cmds.insert(std::make_pair("intersect", zhitnyj::handleIntersect));
  cmds.insert(std::make_pair("union", zhitnyj::handleUnion));

  try {
    zhitnyj::loadTreeFromFile(argv[1], dictionaries);
  } catch (const std::exception &e) {
    std::cerr << "Error loading file: " << e.what() << "\n";
    return 1;
  }

  while (!std::cin.eof()) {
    std::string command;
    std::cin >> command;

    auto commandIter = cmds.find(command);
    if (commandIter != cmds.end() && !command.empty()) {
      commandIter->second(dictionaries);
    }
    else if (!command.empty()) {
      zhitnyj::invalidCommandWarning(std::cout);
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  return 0;
}
