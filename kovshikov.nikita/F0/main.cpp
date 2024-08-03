#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include "createGraph.hpp"
#include "outMessage.hpp"

int main()
{
  using namespace kovshikov;
  Tree< std::string, Graph> graphsList;
  Tree< std::string, std::function< void(Tree< std::string, Graph >&, std::istream&) > > interaction;

  {
    using namespace std::placeholders;
    interaction["create"] = std::bind(createGraph, _1, _2);
    interaction["lonely"] = std::bind(createSingle, _1, _2);
    interaction["delete"] = std::bind(deleteGraph, _1, _2);
    interaction["work"] = std::bind(workWith, _1, _2);
  }

  Tree< std::string, std::function< void(const Tree< std::string, Graph >&, std::ostream&) > > outGraph;

  {
    using namespace std::placeholders;
    outGraph["list"] = std::bind(outputGraphs, _1, _2);
    outGraph["output"] = std::bind(outputVertexes, _1, _2);
  }

  std::string command;
  auto outInvalid = std::bind(outMessage, "<INVALID COMMAND>", std::placeholders::_1);

  while(std::cin >> command)
  {
    if(command == "help")
    {
      outDescription(std::cout);
    }
    else
    {
      try
      {
        if(interaction.find(command) != interaction.end())
        {
          interaction.at(command)(graphsList, std::cin);
        }
        else if(outGraph.find(command) != outGraph.end())
        {
          outGraph.at(command)(graphsList, std::cout);
        }
        else
        {
          outInvalid(std::cout);
          std::cin.clear();
          std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
      }
      catch(const std::logic_error& error)
      {
        std::cout << error.what() << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
  }
}
