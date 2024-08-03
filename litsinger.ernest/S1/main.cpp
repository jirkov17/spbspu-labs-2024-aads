#include <iostream>
#include "list.hpp"
#include "func.hpp"

int main() {
  using namespace litsinger;

  try {
    auto list = listInput(std::cin);
    if (list.isEmpty()) {
      std::cout << "0\n";
      return 0;
    }

    namesOutput(list, std::cout);

    List< List< size_t > > lists;
    listFormation(list, lists);
    if (!lists.isEmpty()) {
      listsOutput(std::cout, lists);

      List<size_t> sums;
      sumsFormation(lists, sums);
      sumsOutput(std::cout, sums);
    }
    return 0;
  } catch (const std::overflow_error& e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "Unhandled exception: " << e.what() << "\n";
    return 2;
  }
}
