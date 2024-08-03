#include <functional>
#include <iomanip>
#include <iostream>
#include "random.hpp"
#include "sort.hpp"

int main(int argc, char ** argv)
{
  if(argc != 4)
  {
    std::cerr << "<THERE SHOULD BE 4 PARAMETERS>" << "\n";
    return 1;
  }

  std::cout << std::fixed << std::setprecision(3);
  using namespace kovshikov;

  std::string compare = argv[1];
  std::string type = argv[2];
  std::string strSize = argv[3];
  bool haveCompare = compare == "ascending" || compare == "descending";
  bool haveType = type == "ints" || type == "floats";

  if(!(haveCompare && haveType))
  {
    std::cerr << "<THE TYPE OR SORTING METHOD IS SPECIFIED INCORRECTLY>" << "\n";
    return 1;
  }

  if(!isDigit(strSize) || strSize == "0")
  {
    std::cerr << "<YOU NEED TO ENTER THE CORRECT SIZE>" << "\n";
    return 1;
  }
  size_t size = std::stoll(strSize);

  Tree< std::string, Tree< std::string, std::function< void(std::ostream& stream, size_t size) > > > allSort;
  Tree< std::string, std::function< void(std::ostream& stream, size_t size) > > intSort;
  Tree< std::string, std::function< void(std::ostream& stream, size_t size) > > floatSort;

  {
    using namespace std::placeholders;
    intSort.insert("ascending", std::bind(sortDataStructures< int, std::less< int > >, _1, _2, std::less< int >{}));
    intSort.insert("descending", std::bind(sortDataStructures< int, std::greater< int > >, _1, _2, std::greater< int >{}));

    floatSort.insert("ascending", std::bind(sortDataStructures< float, std::less< float > >, _1, _2, std::less< float >{}));
    floatSort.insert("descending", std::bind(sortDataStructures< float, std::greater< float > >, _1, _2, std::greater< float >{}));

    allSort.insert("floats", floatSort);
    allSort.insert("ints", intSort);
  }

  allSort.at(type).at(compare)(std::cout, size);

  return 0;
}
