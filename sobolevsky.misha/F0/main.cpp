#include <iostream>
#include <algorithm>
#include <map>
#include <limits>
#include <vector>
#include <memory>
#include <functional>
#include "commands.hpp"
#include "myMap.hpp"
#include "myMultiMap.hpp"
#include "myList.hpp"
#include "utilsForDictsAndErrors.hpp"

int main()
{
  std::cout << "To view the available commands, type \"commands\"\n";
  std::shared_ptr< sobolevsky::List< std::pair< std::string, sobolevsky::MyMultiMap< size_t, std::string > > > > myContainer
  (new sobolevsky::List< std::pair<std::string, sobolevsky::MyMultiMap< size_t, std::string > > >());

  sobolevsky::MyMap< std::string, std::function< void(std::istream & in, std::ostream & out) > > cmds;

  cmds["commands"] = sobolevsky::getCommands;
  cmds["loadAndCreate"] = std::bind(sobolevsky::getLoadAndCreate, myContainer, std::placeholders::_1);
  cmds["allDicts"] = std::bind(sobolevsky::getAllDicts, myContainer, std::placeholders::_1, std::placeholders::_2);
  cmds["delete"] = std::bind(sobolevsky::getDelete, myContainer, std::placeholders::_1);
  cmds["select"] = std::bind(sobolevsky::getSelect, myContainer, std::placeholders::_1, std::placeholders::_2);
  cmds["rename"] = std::bind(sobolevsky::getRename, myContainer, std::placeholders::_1);
  cmds["compareDicts"] = std::bind(sobolevsky::getCompareDicts, myContainer, std::placeholders::_1, std::placeholders::_2);
  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      cmds.at(cmd)(std::cin, std::cout);
    }
    catch(const std::out_of_range & e)
    {
      sobolevsky::error(std::cerr);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      cmds.clear();
    }
  }
  cmds.clear();
  return 0;
}
