#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>
#include <List.hpp>
#include "Commands.hpp"
#include "GraphUtils.hpp"

void resetDijkstra(Graph &graph) {
  graph.distances.clear();
  graph.predecessors.clear();
  for (const auto &pair: graph.adjList) {
    graph.distances[pair.first] = std::numeric_limits< int >::max();
  }
}

void dijkstraCommand(std::istream &input, std::ostream &output, Graph &graph) {
  std::string startVertex;
  input >> startVertex;

  if (graph.adjList.find(startVertex) == graph.adjList.end()) {
    output << "Vertex does not exist\n";
  }
  else {
    resetDijkstra(graph);
    graph.distances[startVertex] = 0;

    zhitnyj::List< std::string > vertices;
    for (const auto &pair: graph.adjList) {
      vertices.push_back(pair.first);
    }

    while (!vertices.empty()) {
      std::string minVertex;
      int minDistance = std::numeric_limits< int >::max();
      for (auto it = vertices.begin(); it != vertices.end(); ++it) {
        const std::string &vertex = *it;
        if (graph.distances[vertex] < minDistance) {
          minDistance = graph.distances[vertex];
          minVertex = vertex;
        }
      }

      if (minDistance == std::numeric_limits< int >::max()) {
        break;
      }

      auto it = vertices.begin();
      while (it != vertices.end()) {
        if (*it == minVertex) {
          vertices.erase(*it);
          break;
        }
        ++it;
      }

      for (const auto &neighborWeightPair: graph.adjList[minVertex]) {
        const std::string &neighbor = neighborWeightPair.first;
        int weight = neighborWeightPair.second;

        int distance = graph.distances[minVertex] + weight;
        if (distance < graph.distances[neighbor]) {
          graph.distances[neighbor] = distance;
          graph.predecessors[neighbor] = minVertex;
        }
      }
    }
  }
}

void shortestPathCommand(std::istream &input, std::ostream &output, const Graph &graph) {
  std::string startVertex, endVertex;
  input >> startVertex >> endVertex;

  if (graph.distances.find(endVertex) == graph.distances.end()) {
    output << "One of the vertices doesn't exists\n";
  }
  else if (graph.distances.at(endVertex) == std::numeric_limits< int >::max()) {
    output << "No path between vertices\n";
  }
  else {
    zhitnyj::List< std::string > path;
    std::string current = endVertex;

    while (current != startVertex) {
      path.push_front(current);
      current = graph.predecessors.at(current);
    }
    path.push_front(startVertex);

    for (const auto &vertex: path) {
      output << vertex << " ";
    }
    output << "\n";
  }
}

void saveGraphCommand(std::istream &input, std::ostream &output, const Graph &graph) {
  std::string filename;
  input >> filename;
  std::ofstream file(filename);
  if (!file) {
    throw std::logic_error("File read/write error\n");
  }

  for (const auto &vertexEdgesPair: graph.adjList) {
    const auto &vertex = vertexEdgesPair.first;
    const auto &edges = vertexEdgesPair.second;
    file << vertex;
    for (const auto &neighborWeightPair: edges) {
      const auto &neighbor = neighborWeightPair.first;
      const auto &weight = neighborWeightPair.second;
      file << " " << neighbor << " " << weight;
    }
    file << "\n";
  }
  output << "Graph was saved in file!\n";
}

zhitnyj::List< std::string > split(const std::string &str) {
  zhitnyj::List< std::string > tokens;
  std::string token;
  size_t start = 0;
  size_t end = 0;

  while ((end = str.find(' ', start)) != std::string::npos) {
    token = str.substr(start, end - start);
    tokens.push_back(token);
    start = end + 1;
  }
  tokens.push_back(str.substr(start));
  return tokens;
}

void loadGraphCommand(std::istream &input, std::ostream &output, Graph &graph) {
  std::string filename;
  input >> filename;
  std::ifstream file(filename);
  if (!file) {
    throw std::logic_error("File not found\n");
  }

  graph.adjList.clear();
  std::string line;

  while (std::getline(file, line)) {
    auto parts = split(line);
    if (parts.size() < 2) {
      output << "Invalid line format: " << line << "\n";
      continue;
    }

    std::string vertex = parts[0];
    if (graph.adjList.find(vertex) == graph.adjList.end()) {
      addVertex(graph, vertex);
    }

    for (size_t i = 1; i < parts.size(); i += 2) {
      if (i + 1 >= parts.size()) {
        output << "Invalid edge format in line: " << line << "\n";
        break;
      }

      std::string neighbor = parts[i];
      int weight;
      try {
        weight = std::stoi(parts[i + 1]);
      } catch (...) {
        output << "Invalid weight format in line: " << line << "\n";
        continue;
      }

      if (graph.adjList.find(neighbor) == graph.adjList.end()) {
        addVertex(graph, neighbor);
      }
      if (graph.adjList[vertex].find(neighbor) == graph.adjList[vertex].end()) {
        addEdge(graph, vertex, neighbor, weight);
      }
    }
  }
}

void addCommand(std::istream &input, std::ostream &output, Graph &graph) {
  std::string type;
  input >> type;

  if (type == "v") {
    std::string vertex;
    input >> vertex;
    addVertex(graph, vertex);
  }
  else if (type == "e") {
    std::string vertex1, vertex2;
    int weight;
    input >> vertex1 >> vertex2 >> weight;
    addEdge(graph, vertex1, vertex2, weight);
  }
  else {
    printInvalidCommand(output);
  }
}

void delCommand(std::istream &input, std::ostream &output, Graph &graph) {
  std::string type;
  input >> type;

  if (type == "v") {
    std::string vertex;
    input >> vertex;
    deleteVertex(graph, vertex);
  }
  else if (type == "e") {
    std::string vertex1, vertex2;
    input >> vertex1 >> vertex2;
    deleteEdge(graph, vertex1, vertex2);
  }
  else {
    printInvalidCommand(output);
  }
}

void showGraphCommand(std::ostream &output, const Graph &graph) {
  for (const auto &vertexEdgesPair: graph.adjList) {
    const auto &vertex = vertexEdgesPair.first;
    const auto &edges = vertexEdgesPair.second;
    output << vertex << ": ";
    for (const auto &neighborWeightPair: edges) {
      const auto &neighbor = neighborWeightPair.first;
      const auto &weight = neighborWeightPair.second;
      output << "(" << neighbor << ", " << weight << ") ";
    }
    output << "\n";
  }
}

void updateEdgeCommand(std::istream &input, std::ostream &output, Graph &graph) {
  std::string type;
  input >> type;

  if (type == "e") {
    std::string vertex1, vertex2;
    int newWeight;
    input >> vertex1 >> vertex2 >> newWeight;
    updateEdge(graph, vertex1, vertex2, newWeight);
  }
  else {
    printInvalidCommand(output);
  }
}

void neighborsCommand(std::istream &input, std::ostream &output, const Graph &graph) {
  std::string vertex;
  input >> vertex;
  neighbors(graph, vertex, output);
}

void isConnectedCommand(std::istream &input, std::ostream &output, const Graph &graph) {
  std::string vertex1, vertex2;
  input >> vertex1 >> vertex2;
  isConnected(graph, vertex1, vertex2, output);
}

void helpCommand(std::ostream &output) {
  output << "Available commands:\n";
  output << "help - Display this help message.\n";
  output << "add v <vertex> - Add a vertex to the graph.\n";
  output << "add e <vertex1> <vertex2> <weight> - Add an edge with a specified weight between two vertices.\n";
  output << "del v <vertex> - Delete a vertex and all its incident edges.\n";
  output << "del e <vertex1> <vertex2> - Delete an edge between two vertices.\n";
  output << "dijkstra <vertex> - Find the shortest paths from the specified vertex to all other vertices using Dijkstra's algorithm.\n";
  output << "path <vertex1> <vertex2> - Display the shortest path from vertex1 to vertex2 after executing Dijkstra's algorithm.\n";
  output << "show - Display the current state of the graph.\n";
  output << "save <file> - Save the current state of the graph to the specified file.\n";
  output << "load <file> - Load the state of the graph from the specified file.\n";
  output << "update e <vertex1> <vertex2> <new weight> - Update the weight of the edge between two vertices.\n";
  output << "neighbors <vertex> - Display all neighbors of the specified vertex.\n";
  output << "connected <vertex1> <vertex2> - Check if there is a path between two vertices.\n";
}

void printInvalidCommand(std::ostream &output) {
  output << "<INVALID COMMAND>\n";
}
