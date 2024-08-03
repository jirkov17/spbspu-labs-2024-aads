#include <iostream>
#include <fstream>
#include <tree.hpp>
#include <functional>
#include "IOFunctions.hpp"
#include "keySumm.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;
  if (argc != 3)
  {
    std::cerr << "Invalid amount of arguments\n";
    return 1;
  }
  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Unable to open the file\n";
    return 1;
  }

  Tree< long long, std::string > data;
  readTree(input, data);
  if (data.empty())
  {
    sendEmpty(std::cout);
    return 0;
  }

  using TraverseMethod = std::function< KeySumm(tree_t*, KeySumm) >;
  Tree< std::string, TraverseMethod > orders;
  orders["ascending"] = &Tree< long long, std::string >::traverseLnR< KeySumm >;
  orders["descending"] = &Tree< long long, std::string >::traverseRnL< KeySumm >;
  orders["breadth"] = &Tree< long long, std::string >::traverseBreadth< KeySumm >;

  KeySumm result;
  try
  {
    result = orders.at(argv[1])(&data, KeySumm());
  }
  catch (const std::out_of_range& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << '\n';
    return 3;
  }
  catch (const std::underflow_error& e)
  {
    std::cerr << e.what() << '\n';
    return 3;
  }

  std::cout << result.getResults() << '\n';

  return 0;
}
