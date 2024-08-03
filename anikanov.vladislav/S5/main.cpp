#include <iostream>
#include <sstream>
#include <string>
#include <binarySearchTree.hpp>

#include "resultCounter.hpp"
#include "mainExtansion.hpp"

int main(int argc, char *argv[])
{
  using namespace anikanov;

  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [ascending|descending|breadth] filename\n";
    printInvalidUsage(std::cerr, argv);
    return 1;
  }

  std::string mode = argv[1];
  std::string filename = argv[2];
  BinarySearchTree< long long, std::string, std::less<> > bst;

  if (!loadTreeFromFile(filename, bst)) {
    return 1;
  }

  ResultCounter result;

  try {
    if (mode == "ascending") {
      result = bst.traverse_lnr(result);
    } else if (mode == "descending") {
      result = bst.traverse_rnl(result);
    } else if (mode == "breadth") {
      result = bst.traverse_breadth(result);
    } else {
      printInvalidMode(std::cerr);
      return 1;
    }
  } catch (const std::runtime_error &e) {
    printError(std::cerr, e.what());
    return 1;
  }

  if (result.getResult() == 0) {
    printEmpty(std::cout);
    return 0;
  }

  std::cout << result.getResult() << " " << result.getValues() << "\n";
  return 0;
}
