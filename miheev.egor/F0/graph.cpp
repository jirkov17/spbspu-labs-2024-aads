#include "graph.hpp"
#include <delimiters.hpp>
#include <algorithm>
#include <utility>
#include <limits>
#include <iterator>
#include <iomanip>

void miheev::Graph::addNode(int name)
{
  if (contains(name))
  {
    throw std::invalid_argument("[ERROR](insertion): the node you want to add already exists");
  }
  nodes_.insert({name, Node{name}});
}

void miheev::Graph::rmNode(int name)
{
  Node& node = nodes_.at(name);
  auto iter(node.edges.begin());
  for (auto iter(node.edges.begin()); !node.edges.empty(); iter = node.edges.begin())
  {
    int neighbourName = iter->dest;
    rmEdge(name, neighbourName);
  }
  nodes_.erase(name);
}

void miheev::Graph::addEdge(int lnode, int rnode, size_t weight)
{
  if (!contains(lnode))
  {
    throw std::invalid_argument("[ERROR](connection): no node named " + std::to_string(lnode));
  }
  if (!contains(rnode))
  {
    throw std::invalid_argument("[ERROR](connection): no node named " + std::to_string(rnode));
  }
  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  Edge fromLeftToRight{rightNode.name, weight};
  Edge fromRightToLeft{leftNode.name, weight};

  leftNode.edges.pushBack(fromLeftToRight);
  leftNode.backLinks.insert({rnode, fromRightToLeft});

  rightNode.edges.pushBack(fromRightToLeft);
  rightNode.backLinks.insert({lnode, fromLeftToRight});
}

void miheev::Graph::rmEdge(int lnode, int rnode)
{
  if (!contains(lnode))
  {
    throw std::invalid_argument("[ERROR](disconnection): node names" + std::to_string(lnode) + " doesn't exist");
  }
  if (!contains(rnode))
  {
    throw std::invalid_argument("[ERROR](disconnection): node names" + std::to_string(rnode) + " doesn't exist");
  }

  Node& leftNode = nodes_[lnode];
  Node& rightNode = nodes_[rnode];

  leftNode.edges.remove(rightNode.backLinks[lnode]);
  rightNode.backLinks.erase(lnode);

  rightNode.edges.remove(leftNode.backLinks[rnode]);
  leftNode.backLinks.erase(rnode);
}

miheev::Graph::Path miheev::Graph::navigate(int start, int finish) const
{
  Dextra dextra(*this);
  Path path = dextra(start, finish);
  return path;
}

std::ostream& miheev::Graph::printNodes(std::ostream& out) const
{
  for (auto cIter(nodes_.cbegin()); cIter != nodes_.cend();)
  {
    out << cIter->first;
    if (++cIter != nodes_.cend())
    {
      out << ' ';
    }
  }
  out << '\n';
  return out;
}

std::ostream& miheev::Graph::printAllEdges(std::ostream& out) const
{
  Printer printer;
  for (auto cIter(nodes_.cbegin()); cIter != nodes_.cend();)
  {
    printer.printUniqueEdges(cIter->second, out);
    if (++cIter == nodes_.cend())
    {
      return out << '\n';
    }
    const Node& nextNode = cIter->second;
    if (printer.hasUniqueEdges(nextNode))
    {
      out << ' ';
    }
  }
  return out << '\n';
}

std::ostream& miheev::Graph::Printer::printUniqueEdges(const Node& node, std::ostream& out)
{
  visitedNodes.pushBack(node.name);
  for (auto cIter(node.edges.cbegin()); cIter != node.edges.cend(); cIter++)
  {
    int destinationName = cIter->dest;
    size_t weight = cIter -> weight;
    bool edgeIsUnique = !visitedNodes.contains(destinationName);
    if (edgeIsUnique)
    {
      if (cIter != node.edges.cbegin())
      {
        out << ' ';
      }
      out << node.name << '-' << destinationName << ':' << weight;
    }
  }
  return out;
}

bool miheev::Graph::Printer::hasUniqueEdges(const Node& node) const
{
  for (auto cIter(node.edges.cbegin()); cIter != node.edges.cend(); cIter++)
  {
    int destName = cIter->dest;
    bool isUnique = !visitedNodes.contains(destName);
    if (isUnique)
    {
      return true;
    }
  }
  return false;
}

size_t miheev::Graph::Edge::HashFunction::operator()(const Edge& rhs) const
{
  size_t ptrHash = std::hash< int >()(rhs.dest);
  size_t weightHash = std::hash< size_t >()(rhs.weight) << 1;
  return ptrHash ^ weightHash;
}

bool miheev::Graph::Edge::operator==(const Edge& rhs) const
{
  return dest == rhs.dest && weight == rhs.weight;
}

miheev::Graph::Dextra::Dextra(const Graph& curGraph):
  graph(curGraph)
{
  for (auto cIter(curGraph.nodes_.cbegin()); cIter != curGraph.nodes_.cend(); cIter++)
  {
    const Node& node = cIter->second;
    unprocessedNodes.pushBack(node.name);
    timeToNodes.insert({node.name, std::numeric_limits< size_t >::max()});
  }
}

miheev::Graph::Path miheev::Graph::Dextra::operator()(int start, int finish)
{
  if (!graph.contains(start))
  {
    throw std::invalid_argument("[ERROR](navigation): no node " + std::to_string(start));
  }
  if (!graph.contains(finish))
  {
    throw std::invalid_argument("[ERROR](navigation): no node " + std::to_string(finish));
  }
  updateNodeState(start, 0);
  calcMinTimeToEach();
  Path path;
  path.lenght = timeToNodes.at(finish);
  path.path = findShortestPath(start, finish);
  return path;
}

void miheev::Graph::Dextra::calcMinTimeToEach()
{
  while(!unprocessedNodes.empty())
  {
    int nameOfNodeWithMinimumTime = getNodeWithMinimumTimeToIt();
    if (timeToNodes.at(nameOfNodeWithMinimumTime) == std::numeric_limits< size_t >::max())
    {
      return;
    }
    const Node& node = graph.nodes_.at(nameOfNodeWithMinimumTime);
    recalculateTimeToNeighboursOfTheNode(node);
    unprocessedNodes.remove(node.name);
  }
}

void miheev::Graph::Dextra::recalculateTimeToNeighboursOfTheNode(const Node& node)
{
  for (auto iter(node.edges.cbegin()); iter != node.edges.cend(); iter++)
  {
    int neighbourName = iter->dest;
    bool neighbourIsUnprocessed = unprocessedNodes.contains(neighbourName);
    if (neighbourIsUnprocessed)
    {
      size_t timeToNeighbour = timeToNodes.at(node.name) + iter->weight;
      if (timeToNeighbour < timeToNodes.at(neighbourName))
      {
        updateNodeState(neighbourName, timeToNeighbour, node.name);
      }
    }
  }
}

int miheev::Graph::Dextra::getNodeWithMinimumTimeToIt()
{
  size_t minTime = std::numeric_limits< size_t >::max();
  int node = -1;
  for (auto iter(unprocessedNodes.cbegin()); iter != unprocessedNodes.cend(); iter++)
  {
    size_t curTime = timeToNodes.at(*iter);
    if (curTime <= minTime)
    {
      node = *iter;
      minTime = curTime;
    }
  }
  return node;
}

miheev::List< int > miheev::Graph::Dextra::findShortestPath(int start, int finish)
{
  if (timeToNodes.at(finish) == std::numeric_limits< size_t >::max())
  {
    std::invalid_argument("[ERROR](navigation): no path exists from node " + std::to_string(start)
     + " to node " + std::to_string(finish) + '\n');
  }
  miheev::List< int > path;
  path.pushFront(finish);
  do
  {
    int parentNode = nodesParrents.at(finish);
    path.pushFront(parentNode);
    finish = parentNode;
  } while (finish != start);
  return path;
}

void miheev::Graph::Dextra::updateNodeState(int node, size_t timeToNode, int parrentNode)
{
  timeToNodes[node] = timeToNode;
  nodesParrents[node] = parrentNode;
}

bool isNewLine(std::istream& in)
{
  in >> std::noskipws;
  char peek = in.peek();
  in >> std::skipws;
  return peek == '\n';
}

std::istream& miheev::operator>>(std::istream& in, Graph& graph)
{
  using del = DelimiterIO;

  int lnode = -1, rnode = -1;
  size_t weight;

  while(!(in.eof() || isNewLine(in)))
  {
    in >> lnode >> del{'-'} >> rnode >> del{':'} >> weight;
    if (in.fail() && !in.eof())
    {
      std::cerr << "Warning: failed to read one of the nodes\n";
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), ' ');
      continue;
    }
    if (!graph.contains(lnode))
    {
      graph.addNode(lnode);
    }
    if (!graph.contains(rnode))
    {
      graph.addNode(rnode);
    }
    graph.addEdge(lnode, rnode, weight);
  }
  return in;
}

bool miheev::Graph::contains(int nodeName) const
{
  return nodes_.contains(nodeName);
}
