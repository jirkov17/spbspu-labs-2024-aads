#ifndef BINARYTREEII_HPP
#define BINARYTREEII_HPP
#include <string>
#include "BinarySearchTree.hpp"

namespace hohlova
{
  void readFile(const std::string& path, BinarySearchTree< int, std::string >& bst);
  int parseNum(const std::string& num);
  void readDataSet(const std::string& dataSet, BinarySearchTree< int, std::string >& bst);
  int sum(int a, int b);
}

#endif
