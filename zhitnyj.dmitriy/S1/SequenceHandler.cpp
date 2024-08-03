#include <iostream>
#include <limits>
#include "SequenceHandler.hpp"

void zhitnyj::SequenceHandler::addSequence(const std::string &name, const zhitnyj::List< unsigned long long > &sequence) {
  names.push_back(name);
  sequences.push_back(sequence);
}

void zhitnyj::SequenceHandler::printSequencesNames() {
  for (auto it = names.begin(); it != names.end(); ++it) {
    std::cout << *it << (it + 1 == names.end() ? "" : " ");
  }
  if (*names.begin() != "") {
    std::cout << "\n";
  }
}

void zhitnyj::SequenceHandler::calculateSums() {
  size_t maxLen = 0;
  for (auto &seq: sequences) {
    maxLen = std::max(maxLen, seq.size());
  }

  unsigned long long *sums = new unsigned long long[maxLen]{};
  for (size_t i = 0; i < maxLen; ++i) {
    for (const auto &seq: sequences) {
      auto it = seq.begin();

      for (size_t j = 0; j < i && it != seq.end(); ++j) {
        ++it;
      }
      if (it != seq.end()) {
        if (sums[i] > std::numeric_limits< unsigned long long >::max() - *it) {
          delete[] sums;
          throw std::overflow_error("Sum of numbers is too big.");
        }
        sums[i] += *it;
      }
    }
  }

  if (!maxLen) {
    std::cout << "0\n";
  }

  for (size_t i = 0; i < maxLen; ++i) {
    std::cout << sums[i] << (i == (maxLen - 1) ? "\n" : " ");
  }

  delete[] sums;
}

void zhitnyj::SequenceHandler::printSequences() {
  size_t maxLen = 0;
  for (auto &seq: sequences) {
    maxLen = std::max(maxLen, seq.size());
  }

  int firstPrint = 0;
  for (size_t i = 0; i < maxLen; ++i) {
    for (const auto &seq: sequences) {
      auto it = seq.begin();

      for (size_t j = 0; j < i && it != seq.end(); ++j) {
        ++it;
      }
      if (it != seq.end()) {
        std::cout << (!firstPrint ? "" : " ") << *it;
        firstPrint = 1;
      }
    }
    std::cout << "\n";
    firstPrint = 0;
  }
}
