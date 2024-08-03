#include <iostream>
#include <string>
#include "SequenceHandler.hpp"

int main() {
  try {
    zhitnyj::SequenceHandler handler;
    std::string line;

    while (std::getline(std::cin, line)) {
      size_t firstSpace = line.find(' ');

      std::string name = line.substr(0, firstSpace);
      std::string numbers = line.substr(firstSpace + 1);

      zhitnyj::List< unsigned long long > sequence;
      size_t pos = 0;

      if (firstSpace == std::string::npos) {
        handler.addSequence(name, sequence);
        continue;
      }
      while (pos < numbers.length()) {
        size_t nextSpace = numbers.find(' ', pos);
        if (nextSpace == std::string::npos) {
          nextSpace = numbers.length();
        }

        unsigned long long number = std::stoull(numbers.substr(pos, nextSpace - pos));
        sequence.push_back(number);

        pos = nextSpace + 1;
      }

      handler.addSequence(name, sequence);
    }

    handler.printSequencesNames();
    handler.printSequences();
    handler.calculateSums();
  }
  catch (const std::overflow_error &err) {
    std::cerr << "There was overflow exception ( " << err.what() << ")\n";
    return 1;
  }
  catch (const std::exception &err) {
    std::cerr << err.what() << "\n";
    return 1;
  }

  return 0;
}
