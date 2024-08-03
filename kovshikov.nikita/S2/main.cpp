#include <cstring>
#include <fstream>
#include "computing.hpp"
#include "queue.hpp"
#include "stack.hpp"

int main(int argc, char ** argv)
{
  using namespace kovshikov;
  Queue< std::string > allData;
  doubleQ separateData;
  doubleQ postfixQ;
  Stack< long long > result;
  if(argc == 1)
  {
    readData(std::cin, allData);
  }
  else if(argc == 2)
  {
    std::ifstream file(argv[1]);
    readData(file, allData);
  }
  else
  {
    std::cout << "Something went wrong." << "\n";
  }
  separateElements(allData, separateData);
  try
  {
    getPostfix(separateData, postfixQ);
    getComputation(postfixQ, result);
  }
  catch(const std::exception &error)
  {
    std::cerr << error.what() << "\n";
    return 1;
  }
  output(std::cout, result);
  return 0;
}
