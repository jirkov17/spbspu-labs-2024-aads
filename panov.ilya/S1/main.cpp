#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "list.hpp"

int main() {
  Panov::List<std::pair<std::string, std::vector<int>>> sequences;

  std::string line;
  while (std::getline(std::cin, line)) {
    std::istringstream iss(line);
    std::string name;
    iss >> name;
    if (name.empty())
      break;

    std::vector<int> sequence;
    int num;
    while (iss >> num)
      sequence.push_back(num);

    sequences.push_back({ name, sequence });
  }

  for (const auto& seq : sequences)
    std::cout << seq.first << ' ';
  std::cout << std::endl;

  size_t maxLength = 0;
  for (const auto& seq : sequences)
    maxLength = std::max(maxLength, seq.second.size());

  for (size_t i = 0; i < maxLength; ++i) {
    for (const auto& seq : sequences) {
      if (i < seq.second.size())
        std::cout << seq.second[i] << ' ';
    }
    std::cout << std::endl;
  }

  for (size_t i = 0; i < maxLength; ++i) {
    int sum = 0;
    for (const auto& seq : sequences) {
      if (i < seq.second.size())
        sum += seq.second[i];
    }
    std::cout << sum << ' ';
  }
  std::cout << std::endl;

  return 0;
}
