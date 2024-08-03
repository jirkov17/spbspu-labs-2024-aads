#include <iostream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <limits>

int main() {
  std::vector<std::pair<std::string, std::vector<uint64_t>>> data;
  std::vector<uint64_t> totals;
  std::string line, word, number;
  bool hasData = false;

  while (std::getline(std::cin, line)) {
    if (line.empty())
      break;
    std::istringstream ss(line);
    ss >> word;

    std::vector<uint64_t> values;
    while (ss >> number) {
      try {
        values.push_back(std::stoull(number));
      }
      catch (const std::invalid_argument& e) {
        std::cerr << "Invalid number: " << number << '\n';
        return 1;
      }
      catch (const std::out_of_range& e) {
        std::cerr << "Number out of range: " << number << '\n';
        return 1;
      }
    }
    data.push_back({ word, values });
    hasData = true;
  }

  if (!hasData) {
    std::cout << 0 << '\n';
    return 0;
  }

  size_t maxLength = 0;
  for (const auto& entry : data)
    maxLength = std::max(maxLength, entry.second.size());

  for (auto it = data.begin(); it != data.end(); ++it) {
    std::cout << it->first;
    auto nextIt = it;
    ++nextIt;
    if (nextIt != data.end())
      std::cout << " ";
  }
  std::cout << std::endl;

  size_t maxValueCount = 0;
  for (const auto& entry : data)
    maxValueCount = std::max(maxValueCount, entry.second.size());

  if (maxValueCount == 0) {
    std::cout << 0 << std::endl;
    return 0;
  }

  for (size_t i = 0; i < maxValueCount; ++i) {
    bool hasValue = false;
    for (const auto& entry : data) {
      if (i < entry.second.size()) {
        if (hasValue)
          std::cout << " ";
        std::cout << entry.second[i];
        hasValue = true;
      }
    }
    std::cout << std::endl;
  }

  try {
    for (size_t i = 0; i < maxLength; ++i) {
      uint64_t sum = 0;
      for (auto it = data.begin(); it != data.end(); ++it) {
        if (i < it->second.size()) {
          if (sum > std::numeric_limits<uint64_t>::max() - it->second[i])
            throw std::overflow_error("Overflow");
          sum += it->second[i];
        }
      }
      totals.push_back(sum);
    }
  }
  catch (const std::overflow_error& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  for (auto it = totals.begin(); it != totals.end(); ++it) {
    std::cout << *it;
    auto nextIt = it;
    ++nextIt;
    if (nextIt != totals.end())
      std::cout << " ";
  }
  std::cout << "\n";

  return 0;
}
