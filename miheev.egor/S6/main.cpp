#include <iostream>
#include <tree.hpp>
#include <string>
#include "IOProcessing.hpp"
#include "messages.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;

  srand(42);

  if (argc != 4)
  {
    errorWrapper(std::cerr, messages::sendWrongAmountOfArgs);
    return 1;
  }

  size_t size = 0;
  try
  {
    size = std::stoull(argv[3]);
  }
  catch(const std::invalid_argument& e)
  {
    errorWrapper(std::cerr, messages::sendInvalidConversion);
    return 2;
  }

  if (size < 1)
  {
    errorWrapper(std::cerr, messages::sendInapropriateParameter);
    return 2;
  }

  using SortFunctions = Tree< std::string, std::function< void(std::ostream&, size_t) > >;
  Tree < std::string, SortFunctions > typedFuncs;
  {
    using namespace std::placeholders;
    typedFuncs["floats"]["ascending"] = std::bind(miheev::testSorts< double, std::less< double> >, _1, _2, std::less< double >{});
    typedFuncs["floats"]["descending"] = std::bind(miheev::testSorts< double, std::greater< double> >, _1, _2, std::greater< double >{});
    typedFuncs["ints"]["ascending"] = std::bind(miheev::testSorts< int, std::less< int> >, _1, _2, std::less< int >{});
    typedFuncs["ints"]["descending"] = std::bind(miheev::testSorts< int, std::greater< int> >, _1, _2, std::greater< int >{});
  }

  if (!typedFuncs.contains(argv[2]))
  {
    errorWrapper(std::cerr, messages::sendInvalidSecondArgument);
    return 3;
  }
  if (!typedFuncs.at(argv[2]).contains(argv[1]))
  {
    errorWrapper(std::cerr, messages::sendInvalidFirstArgument);
    return 3;
  }

  typedFuncs.at(argv[2]).at(argv[1])(std::cout, size);

  return 0;
}
