#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include "BinaryTreeII.hpp"
#include "keySumm.hpp"
#include "BinarySearchTree.hpp"

int main(int argc, char** argv)
{
  if (argc != 3)
  {
    std::cerr << "Error\n";
    return 1;
  }
  try
  {
    BinarySearchTree< int, std::string > bst;
    hohlova::readFile(argv[2], bst);
    Key_summ f;
    Key_summ res;
    std::string cmd = argv[1];
    if (cmd == "ascending")
    {
      res = bst.traverse_lnr(f);
    }
    else if (cmd == "descending")
    {
      res = bst.traverse_rnr(f);
    }
    else if (cmd == "breadth")
    {
      res = bst.traverse_breadth(f);
    }
    else
    {
      throw std::runtime_error("Invalid command");
    }
    if (res.result_)
    {
      std::cout << res.result_;
    }
    if (!res.str.empty())
    {
      std::cout << " " << res.str << "\n";
    }
  }
  catch (const std::exception& err)
  {
    std::cout << err.what();
    return 1;
  }
  return 0;
}
