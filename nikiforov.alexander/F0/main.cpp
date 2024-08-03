#include <iostream>
#include <functional>
#include "dictionaryCommands.hpp"

int main()
{
  using mapDictionaries_t = nikiforov::AvlTree< std::string, nikiforov::AvlTree< std::string, size_t > >;

  mapDictionaries_t mapDictionaries;

  using namespace std::placeholders;
  std::map< std::string, std::function < void(mapDictionaries_t&, std::istream&, std::ostream&, std::string&) > > command;
  {
    command.emplace("help", std::bind(nikiforov::printCommands, _3));
    command.emplace("create", std::bind(nikiforov::createDict, _1, _2, _3, ""));
    command.emplace("open", std::bind(nikiforov::open, _1, _2, _3));
    command.emplace("delete", std::bind(nikiforov::deleteDict, _1, _2, _3));;
    command.emplace("list", std::bind(nikiforov::printNamesDictionaries, _1, _3));
    command.emplace("add", std::bind(nikiforov::add, _1, _2, _3));
    command.emplace("unite", std::bind(nikiforov::unit, _1, _2, _3));
    command.emplace("rename", std::bind(nikiforov::rename, _1, _2, _3));
    command.emplace("clear", std::bind(nikiforov::clear, _1, _2, _3));
    command.emplace("save", std::bind(nikiforov::save, _1, _2, _3));
    command.emplace("select", nikiforov::select);
    command.emplace("print", nikiforov::printDict);
    command.emplace("find", nikiforov::find);
    command.emplace("erase", nikiforov::erase);
  }

  std::string cmd;
  std::string nameSelectDict = "";

  std::cout << "Enter any valid command (the 'help' command to output all available commands)\n";
  while (std::cin >> cmd)
  {
    try
    {
      command.at(cmd)(mapDictionaries, std::cin, std::cout, nameSelectDict);
    }
    catch (const std::out_of_range&)
    {
      nikiforov::errorMessage(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (const std::exception& e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
  }
  return 0;
}
