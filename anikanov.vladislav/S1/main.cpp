#include <iostream>
#include <memory>
#include "mainExtensions.hpp"

int main()
{
  using namespace anikanov;

  std::unique_ptr< mainList > lists(new mainList);
  inputList(lists, std::cin);

  if (!printNames(lists, std::cout)) {
    return 0;
  }

  getSums response = countList(lists, std::cout);
  List< unsigned long long > sums = response.first;
  bool badSum = response.second;

  if (badSum) {
    std::cerr << "overflow\n";
    return 1;
  }

  printList(sums, std::cout);

  std::cout << "\n";
  return 0;
}
