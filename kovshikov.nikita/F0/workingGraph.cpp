#include "workingGraph.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include "outMessage.hpp"

bool kovshikov::isDigit(char ch)
{
  return std::isdigit(ch);
}

void kovshikov::add(Graph& graph, std::istream& is)
{
  std::string parameter;
  size_t key;
  is >> parameter;
  is >> key;
  if(graph.haveThisKey(key) == true)
  {
    throw std::logic_error("This key is already in use");
  }
  else
  {
    if(std::all_of(parameter.begin(), parameter.end(), isDigit) == true)
    {
      unsigned long long count = std::stoll(parameter);
      std::string graphname;
      is >> graphname;
      graph.addVertex(key, graphname);
      graph.connect(key, count, 1);
    }
    else
    {
      graph.addVertex(key, parameter);
    }
  }
}

std::string kovshikov::getGraphname(std::pair< std::string, Graph > element)
{
  return element.first;
}

void kovshikov::connect(Graph& graph, std::istream& is)
{
  size_t keyWhoOrNum;
  size_t whoOrWith;
  size_t vertexWith;
  is >> keyWhoOrNum >> whoOrWith;
  if(is.peek() == '\n')
  {
    std::cout << graph.getWeight(keyWhoOrNum, whoOrWith) << "\n";
  }
  else
  {
    is >> vertexWith;
    graph.createEdge(whoOrWith, vertexWith, keyWhoOrNum);
  }
}

void kovshikov::getDouble(Graph& graph, std::istream& is)
{
  size_t keyWhoOrNum;
  size_t whoOrWith;
  size_t vertexWith;
  is >> keyWhoOrNum >> whoOrWith;
  auto outTrue = std::bind(outMessage, "TRUE", std::placeholders::_1);
  auto outFalse = std::bind(outMessage, "FALSE", std::placeholders::_1);
  if(is.peek() == '\n')
  {
    if(graph.isDouble(keyWhoOrNum, whoOrWith) == true)
    {
      outTrue(std::cout);
    }
    else
    {
      outFalse(std::cout);
    }
  }
  else
  {
    is >> vertexWith;
    graph.createEdge(whoOrWith, vertexWith, keyWhoOrNum);
    graph.createEdge(vertexWith, whoOrWith, keyWhoOrNum);
  }
}

void kovshikov::deleteElement(Graph& graph, std::istream& is)
{
  size_t keyOrNum;
  size_t vertexWho;
  size_t vertexWith;
  is >> keyOrNum;
  if(is.peek() == '\n')
  {
    graph.deleteVertex(keyOrNum);
  }
  else
  {
    is >> vertexWho >> vertexWith;
    try
    {
      graph.decreaseWeight(vertexWho, vertexWith, keyOrNum);
    }
    catch(const std::logic_error& e)
    {
      throw;
    }
  }
}

void kovshikov::getWeight(Graph& graph, std::istream& is)
{
  size_t key;
  is >> key;
  std::cout << graph.getVertexWeight(key) << "\n";
}

void kovshikov::getDegree(Graph& graph, std::istream& is)
{
  size_t key;
  is >> key;
  std::cout << graph.getDegree(key) << "\n";
}

void kovshikov::getOwn(Graph& graph, std::istream& is)
{
  size_t key;
  is >> key;
  std::cout << graph.getOwn(key) << "\n";
}

void kovshikov::getCountVertex(Graph& graph, std::ostream& out)
{
  out << graph.getSize() << "\n";
}

void kovshikov::outEdge(Graph& graph, std::ostream& out)
{
  out << graph.getEdges() << "\n";
}

void kovshikov::outMax(Graph& graph, std::ostream& out)
{
  graph.getMax(out);
}

void kovshikov::outName(std::string key, std::ostream& out)
{
  out << key << "\n";
}

void kovshikov::change(Graph& graph, std::istream& is)
{
  size_t count;
  size_t who;
  size_t with;
  is >> count >> who >> with;
  graph.change(count, who, with);
}
