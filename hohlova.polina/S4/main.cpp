#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <BinarySearchTree.hpp>
#include "WorkerBST.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Error!";
    return 1;
  }
  Dictionary bst;
  try
  {
    readFile(bst, argv[1]);
    Menu(bst);
  }
  catch (const std::exception& err)
  {
    std::cout << err.what();
    clearTree(bst);
    return 1;
  }
  clearTree(bst);
  return 0;
}
