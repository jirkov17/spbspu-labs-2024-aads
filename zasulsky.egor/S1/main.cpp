#include <iostream>
#include <string>
#include <utility>
#include "ForwardList.hpp"
#include "Vector.hpp"
#include "functions.hpp"

int main()
{
  try
  {
    std::string str;
    bool isOver = false;
    zasulsky::ForwardList < std::pair< std::string, zasulsky::VectorReplica< std::string > > > list;
    while (!std::cin.eof())
    {
      std::getline(std::cin, str);
      getSequence(list, str);
    }
    outputNames(list, std::cout);
    outputSequence(list, std::cout, isOver);
    if (isOver)
    {
      return 1;
    }
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "incorrect use of programm\n";
    return 1;
  }
}
