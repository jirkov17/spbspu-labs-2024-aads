#include <functional>
#include <numeric>
#include "graph.hpp"
#include "commands.hpp"

int main()
{
  using namespace khoroshkin;

  Graph< int > graph;
  Tree< std::string, std::function< void(std::ostream & out) > > availableCmds;
  {
    using namespace std::placeholders;
    availableCmds.insert("help", std::bind(khoroshkin::helpCmd, _1));
    availableCmds.insert("open", std::bind(khoroshkin::openCmd, std::ref(graph), std::ref(std::cin), _1));
    availableCmds.insert("input", std::bind(khoroshkin::inputCmd, std::ref(graph), std::ref(std::cin), _1));
    availableCmds.insert("print", std::bind(khoroshkin::printCmd, std::ref(graph), std::ref(std::cin), _1));
    availableCmds.insert("edge", std::bind(khoroshkin::edgeCmd, std::ref(graph), std::ref(std::cin), _1));
    availableCmds.insert("sort", std::bind(khoroshkin::sortCmd, std::ref(graph), std::ref(std::cin), _1));
    availableCmds.insert("save", std::bind(khoroshkin::saveCmd, std::ref(graph), std::ref(std::cin), _1));
  }

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      auto func = availableCmds.find(cmd);
      if (func == availableCmds.end())
      {
        throw std::out_of_range("");
      }
      (*func).second(std::cout);
    }
    catch(const std::exception & e)
    {
      outInvalidcommand(std::cerr);
    }
  }
  return 0;
}
