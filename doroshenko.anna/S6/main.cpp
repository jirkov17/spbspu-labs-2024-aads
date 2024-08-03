#include <iostream>
#include <stdexcept>
#include "sort.hpp"
#include "BinarySearchTree.hpp"

int main(int argc, char* argv[])
{
  using namespace doroshenko;
  if (argc != 4)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  std::string cmp = argv[1];
  std::string type = argv[2];
  std::string stringSize = argv[3];

  if ((cmp != "ascending" && cmp != "descending") || (type != "ints" && type != "floats"))
  {
    std::cerr << "Wrong input\n";
    return 1;
  }

  size_t size;
  try
  {
    size = std::stoll(stringSize);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  if (size == 0)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }

  BST< std::string, BST< std::string, std::function< void(std::ostream& stream, std::string type, size_t size) > > > sorts;
  BST< std::string, std::function< void(std::ostream& stream, std::string type, size_t size) > > ints;
  BST< std::string, std::function< void(std::ostream& stream, std::string type, size_t size) > > floats;

  using namespace std::placeholders;
  ints.insert("ascending", std::bind(sortData< int, std::less< int > >, _1, _2, _3, std::less< int >{}));
  ints.insert("descending", std::bind(sortData< int, std::greater< int > >, _1, _2, _3, std::greater< int >{}));

  floats.insert("ascending", std::bind(sortData< float, std::less< float > >, _1, _2, _3, std::less< float >{}));
  floats.insert("descending", std::bind(sortData< float, std::greater< float > >, _1, _2, _3, std::greater< float >{}));

  sorts.insert("floats", floats);
  sorts.insert("ints", ints);

  sorts.at(type).second.at(cmp).second(std::cout, type, size);
  return 0;
}
