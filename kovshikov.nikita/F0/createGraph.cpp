#include "createGraph.hpp"
#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <sstream>
#include "outMessage.hpp"

void kovshikov::createGraph(Tree< std::string, Graph >& graphsList, std::istream& is)
{
  std::string parameter;
  is >> parameter;
  if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
  {
    unsigned long long count = std::stoll(parameter);
    Graph graph;
    for(size_t i = 1; i <= count; i++)
    {
      graph.addVertex(i, "vertex");
    }
    for(size_t i = 1; i <= count; i++)
    {
      for(size_t j = 1; j <= count; j++)
      {
        if(i != j)
        {
          graph.createEdge(i, j, 1);
        }
      }
    }
    std::string graphname;
    is >> graphname;
    graphsList[graphname] = graph;
  }
  else
  {
    graphsList[parameter];
  }
}

void kovshikov::createSingle(Tree< std::string, Graph >& graphsList, std::istream& is)
{
  std::string graphname;
  is >> graphname;
  std::string parameter;
  is >> parameter;
  if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
  {
    unsigned long long count = std::stoll(parameter);
    Graph graph;
    for(size_t i = 1; i <= count; i++)
    {
      graph.addVertex(i, "vertex");
    }
    graphsList[graphname] = graph;
  }
  else
  {
    throw std::logic_error("This is not number");
  }
}

void kovshikov::deleteGraph(Tree< std::string, Graph >& graphsList, std::istream& is)
{
  std::string key;
  is >> key;
  if(graphsList.find(key) == graphsList.end())
  {
    throw std::logic_error("This graph is not there");
  }
  else
  {
    graphsList.erase(key);
  }
}

void kovshikov::workWith(Tree< std::string, Graph >& graphsList, std::istream& is)
{
  std::string key;
  is >> key;
  if(graphsList.find(key) == graphsList.end())
  {
    throw std::logic_error("This graph is not there");
  }

  Tree< std::string, std::function< void(Graph& graph, std::istream& is) > > working;
  {
    using namespace std::placeholders;
    working["add"] = std::bind(add, _1, _2);
    working["connect"] = std::bind(connect, _1, _2);
    working["double"] = std::bind(getDouble, _1, _2);
    working["delete"] = std::bind(deleteElement, _1, _2);
    working["weight"] = std::bind(getWeight, _1, _2);
    working["degree"] = std::bind(getDegree, _1, _2);
    working["own"] = std::bind(getOwn, _1, _2);
    working["change"] = std::bind(change, _1, _2);
  }

  Tree< std::string, std::function< void(Graph& graph, std::ostream& out) > > outInThisGraph;
  {
    using namespace std::placeholders;
    outInThisGraph["vertex"] = std::bind(getCountVertex, _1, _2);
    outInThisGraph["edge"] = std::bind(outEdge, _1, _2);
    outInThisGraph["max"] = std::bind(outMax, _1, _2);
  }

  std::string command;
  bool isError = false;
  bool end = false;
  auto outInvalid = std::bind(outMessage, "<INVALID COMMAND>", std::placeholders::_1);

  while(end == false && is >> command)
  {
    isError = false;
    try
    {
      if(working.find(command) != working.end())
      {
        working.at(command)(graphsList.at(key), is);
      }
      else if(outInThisGraph.find(command) != outInThisGraph.end())
      {
        outInThisGraph.at(command)(graphsList.at(key), std::cout);
      }
      else if(command == "graphname")
      {
        outName(key, std::cout);
      }
      else
      {
        isError = true;
        outInvalid(std::cout);
        is.clear();
        is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      }
    }
    catch(const std::logic_error& error)
    {
      isError = true;
      std::cout << error.what() << "\n";
      is.clear();
      is.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    if(isError == true && is.peek() == '\n')
    {
      end = true;
    }
    else if(isError == false)
    {
      if(is.get() == '\n' && is.peek() == '\n')
      {
        end = true;
      }
      else
      {
        is.putback('\n');
      }
    }
  }
}

void kovshikov::outputGraphs(const Tree< std::string, Graph >& graphsList, std::ostream& out)
{
  DoubleList< std::string > graphnames;
  std::transform(graphsList.begin(), graphsList.end(), std::back_inserter(graphnames), getGraphname);
  using output_it = std::ostream_iterator< std::string >;
  std::copy(graphnames.begin(), graphnames.end(), output_it{out, " "});
  out << "\n";
}

void kovshikov::outputVertexes(const Tree< std::string, Graph >& graphsList, std::ostream& out)
{
  std::string graphname;
  std::cin >> graphname;
  auto outInvalid = std::bind(outMessage, "The entered graph is missing", std::placeholders::_1);
  if(graphsList.find(graphname) == graphsList.end())
  {
    outInvalid(out);
  }
  else
  {
    graphsList.at(graphname).outGraph(out);
  }
}
