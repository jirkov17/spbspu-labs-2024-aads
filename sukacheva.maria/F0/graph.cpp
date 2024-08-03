#include "graph.hpp"
#include <limits>
#include <stdexcept>
#include <iostream>
#include "BST.hpp"
#include "List.hpp"

namespace sukacheva
{
  Graph::Graph(std::string GraphName_) :
    GraphName(GraphName_),
    AdjacencyList()
  {}

  void Graph::addVertex(std::string& name)
  {
    if (isVertexExist(name))
    {
      throw std::logic_error("Vertex with this name already exists.\n");
    }
    size_t key = AdjacencyList.size();
    VertexesList.insert(key, name);
    BST< size_t, size_t > edges;
    AdjacencyList.insert(key, edges);
  }

  bool Graph::isEdgeExist(std::string& start, std::string& end)
  {
    size_t keyStart = getVertexIndex(start);
    size_t keyEnd = getVertexIndex(end);
    auto it = AdjacencyList[keyStart].find(keyEnd);
    if (it != AdjacencyList[keyStart].end())
    {
      return true;
    }
    return false;
  }

  void Graph::addEdge(std::string& start, std::string& end, size_t weight)
  {
    size_t keyStart = getVertexIndex(start);
    size_t keyEnd = getVertexIndex(end);
    if (keyStart == keyEnd)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
    if (isEdgeExist(start, end))
    {
      throw std::logic_error("Edge between these vertices already exists.\n");
    }
    AdjacencyList[keyStart][keyEnd] = weight;
    AdjacencyList[keyEnd][keyStart] = weight;
  }

  void Graph::deleteVertex(std::string name)
  {
    size_t key = getVertexIndex(name);
    AdjacencyList.erase(key);
    VertexesList.erase(key);
    BST< size_t, std::string > updatedVertexesList;
    for (auto it = VertexesList.begin(); it != VertexesList.end(); ++it)
    {
      size_t newKey = it->first > key ? it->first - 1 : it->first;
      updatedVertexesList.insert(newKey, it->second);
    }
    VertexesList = std::move(updatedVertexesList);
    BST< size_t, BST< size_t, size_t > > updatedAdjacencyList;
    for (auto it = AdjacencyList.begin(); it != AdjacencyList.end(); ++it)
    {
      size_t newKey = it->first > key ? it->first - 1 : it->first;
      BST< size_t, size_t > updatedAdj;
      for (auto adjIt = it->second.begin(); adjIt != it->second.end(); ++adjIt)
      {
        size_t adjKey = adjIt->first > key ? adjIt->first - 1 : adjIt->first;
        updatedAdj.insert(adjKey, adjIt->second);
      }
      updatedAdjacencyList.insert(newKey, std::move(updatedAdj));
    }
    AdjacencyList = std::move(updatedAdjacencyList);
  }

  void Graph::deleteEdge(std::string start, std::string end)
  {
    size_t keyStart = getVertexIndex(start);
    size_t keyEnd = getVertexIndex(end);
    if (keyStart != keyEnd)
    {
      AdjacencyList[keyStart].erase(keyEnd);
      AdjacencyList[keyEnd].erase(keyStart);
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }

  size_t Graph::capacity()
  {
    return AdjacencyList.size();
  }

  void Graph::clear()
  {
    AdjacencyList.clear();
    VertexesList.clear();
  }

  size_t Graph::getVertexIndex(std::string& name)
  {
    auto it = VertexesList.end();
    for (auto iter = VertexesList.begin(); iter != VertexesList.end(); ++iter)
    {
      if (iter->second == name)
      {
        it = iter;
        break;
      }
    }
    if (it != VertexesList.end())
    {
      return it->first;
    }
    else
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }

  std::pair< BST< size_t, size_t >, BST< size_t, size_t > > Graph::dijkstraDistances(std::string name)
  {
    size_t startKey = getVertexIndex(name);
    BST< size_t, size_t > distances;
    BST< size_t, size_t > predecessors;
    BST< size_t, bool > visited;
    for (auto it = VertexesList.begin(); it != VertexesList.end(); ++it)
    {
      distances.insert(it->first, std::numeric_limits<size_t>::max());
    }
    for (auto it = VertexesList.begin(); it != VertexesList.end(); ++it)
    {
      visited.insert(it->first, false);
    }
    distances[startKey] = 0;

    for (size_t i = 0; i < VertexesList.size(); ++i)
    {
      size_t minDistance = std::numeric_limits< size_t >::max();
      size_t minVertex = startKey;
      for (BST< size_t, size_t >::Iterator it = distances.begin(); it != distances.end(); it++)
      {
        if (!visited[it->first] && it->second <= minDistance)
        {
          minDistance = it->second;
          minVertex = it->first;
        }
      }
      if (minDistance == std::numeric_limits< size_t >::max())
      {
        predecessors[i] = std::numeric_limits< size_t >::max();
        break;
      }
      visited[minVertex] = true;
      for (BST< size_t, size_t >::Iterator it = AdjacencyList[minVertex].begin(); it != AdjacencyList[minVertex].end(); it++)
      {
        if (!visited[it->first] && distances[minVertex] + it->second < distances[it->first])
        {
          distances[it->first] = distances[minVertex] + it->second;
          predecessors[it->first] = minVertex;
        }
      }
    }
    std::pair< BST< size_t, size_t >, BST< size_t, size_t > > result = { distances, predecessors };
    return result;
  }

  List< std::string > Graph::dijkstraPath(const BST<size_t, size_t>& predecessors, std::string start, std::string end)
  {
    List< std::string > path;
    size_t keyStart = getVertexIndex(start);
    size_t keyEnd = getVertexIndex(end);
    for (size_t at = keyEnd; at != keyStart; at = predecessors[at])
    {
      if (at == std::numeric_limits< size_t >::max())
      {
        path.pushFront("unattainable");
        return path;
      }
      path.pushFront(VertexesList[at]);
    }
    path.pushFront(VertexesList[keyStart]);
    return path;
  }

  List< List< size_t > > Graph::weightTable()
  {
    size_t vertexCount = VertexesList.size();
    List< List< size_t > > matrix(vertexCount, List< size_t >(vertexCount, std::numeric_limits< size_t >::max()));
    for (size_t i = 0; i < vertexCount; ++i)
    {
      *matrix[i]->operator[](i) = 0;
    }
    for (auto it = AdjacencyList.cbegin(); it != AdjacencyList.cend(); ++it)
    {
      size_t from = it->first;
      const auto& edges = it->second;
      for (auto edgeIt = edges.cbegin(); edgeIt != edges.cend(); ++edgeIt)
      {
        size_t to = edgeIt->first;
        size_t weight = edgeIt->second;
        *matrix[from]->operator[](to) = weight;
      }
    }
    return matrix;
  }

  bool Graph::isVertexExist(std::string& name)
  {
    auto it = VertexesList.end();
    for (auto iter = VertexesList.begin(); iter != VertexesList.end(); ++iter)
    {
      if (iter->second == name)
      {
        it = iter;
        break;
      }
    }
    if (it != VertexesList.end())
    {
      return true;
    }
    return false;
  }

  std::istream& operator>>(std::istream& in, Graph& applicant)
  {
    std::istream::sentry guard(in);
    Graph graph;
    if (!guard)
    {
      return in;
    }
    size_t vertices = 0;
    size_t edges = 0;
    in >> graph.GraphName >> vertices >> edges;
    for (size_t i = 0; i < edges + 1; i++)
    {
      std::string start;
      std::string end;
      size_t weight;
      std::istream::pos_type startPos = in.tellg();
      if (!(in >> start) || !(in >> end) || !(in >> weight))
      {
        in.clear();
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        in.seekg(startPos);
        break;
      }
      else
      {
        if (!graph.isVertexExist(start))
        {
          graph.addVertex(start);
        }
        if (!graph.isVertexExist(end))
        {
          graph.addVertex(end);
        }
        if (!graph.isEdgeExist(start, end))
        {
          graph.addEdge(start, end, weight);
        }
      }
      if (in)
      {
        applicant = graph;
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    return in;
  }
}
