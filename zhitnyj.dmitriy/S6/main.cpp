#include <iostream>
#include <string>
#include <list>
#include <deque>
#include <functional>
#include <List.hpp>
#include "sortOperations.hpp"
#include "random.hpp"

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: ./lab [ascending|descending] [ints|floats] [size]" << std::endl;
    return 1;
  }

  try {
    bool ascending = std::string(argv[1]) == "ascending";
    bool isInt = std::string(argv[2]) == "ints";
    size_t size = std::stoi(argv[3]);

    if (size < 1) {
      std::cerr << "Size must be bigger then 0!\n";
      return 1;
    }

    if (isInt) {
      zhitnyj::List< int > singleList;
      std::list< int > doubleList;
      std::deque< int > deq;
      zhitnyj::generateNumbers(singleList, doubleList, deq, size, true);
      zhitnyj::performSorts(singleList, doubleList, deq, ascending, std::cout);
    }
    else {
      zhitnyj::List< float > singleList;
      std::list< float > doubleList;
      std::deque< float > deq;
      zhitnyj::generateNumbers(singleList, doubleList, deq, size, false);
      zhitnyj::performSorts(singleList, doubleList, deq, ascending, std::cout);
    }
  }
  catch (const std::exception &e) {
    std::cerr << e.what() << "\n";
    return 1;
  }

  return 0;
}
