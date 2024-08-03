#include <iostream>
#include <exception>
#include "stack.hpp"
#include "queue.hpp"
#include "input.hpp"
#include "math.hpp"

int main(int argc, char * argv[])
{
  zheleznyakov::Stack< std::string > problems;
  if (argc == 2)
  {
    std::ifstream input(argv[1]);
    zheleznyakov::readLines(input, problems);
  }
  else if (argc == 1)
  {
    zheleznyakov::readLines(std::cin, problems);
  }
  else
  {
    std::cerr << "Bad arguments\n";
    return 1;
  }
  try
  {
    zheleznyakov::processProblems(problems);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}
