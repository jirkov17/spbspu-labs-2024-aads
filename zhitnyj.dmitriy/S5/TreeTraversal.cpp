#include <iostream>
#include "TreeTraversal.hpp"
#include "KeySum.hpp"

void zhitnyj::traverseAscending(const zhitnyj::BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    zhitnyj::KeySum keySumCounter;
    zhitnyj::KeySum keySumCounter_ = tree.traverse_lnr(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void zhitnyj::traverseDescending(const zhitnyj::BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    zhitnyj::KeySum keySumCounter;
    zhitnyj::KeySum keySumCounter_ = tree.traverse_rnl(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void zhitnyj::traverseBreadth(const zhitnyj::BSTree< long long, std::string > &tree) {
  if (tree.empty()) {
    emptyCommandWarning(std::cout);
  }
  else {
    zhitnyj::KeySum keySumCounter;
    zhitnyj::KeySum keySumCounter_ = tree.traverse_breadth(keySumCounter);

    printResult(keySumCounter_, std::cout);
  }
}

void zhitnyj::printResult(zhitnyj::KeySum &keySumCounter, std::ostream &os) {
  os << keySumCounter.result_;

  while (!keySumCounter.queue.empty()) {
    const auto &kv = keySumCounter.queue.front();
    os << " " << kv.second;
    keySumCounter.queue.pop();
  }

  os << "\n";
}

void zhitnyj::emptyCommandWarning(std::ostream &out) {
  out << "<EMPTY>\n";
}

void zhitnyj::invalidCommandError(std::ostream &out) {
  out << "<INVALID COMMAND>\n";
}
