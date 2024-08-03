#include "myAlgorithms.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <list.hpp>

bool anikanov::checkMatrix(List< List< int > > &matrix)
{
  int n = matrix.size();

  for (int i = 0; i < n; ++i) {
    if (matrix[i][i] != 0) {
      return false;
    }
    for (int j = 0; j < i; ++j) {
      if (matrix[i][j] < 0 || matrix[j][i] < 0) {
        return false;
      }
      if (matrix[i][j] != matrix[j][i]) {
        return false;
      }
    }
  }

  return true;
}

anikanov::List< anikanov::List< int > > anikanov::getEdges(List< List< int > > &graph)
{
  List< List< int > > edges;
  int n = graph.size();

  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      if (graph[i][j] != 0) {
        edges.push_back(List< int >{i, j, graph[i][j]});
      }
    }
  }

  return edges;
}

int anikanov::findParent(List< int > &parent, int i)
{
  if (parent[i] != i) {
    parent[i] = findParent(parent, parent[i]);
  }
  return parent[i];
}

void anikanov::merge(List< int > &parent, List< int > &rank, int x, int y)
{
  int xroot = findParent(parent, x);
  int yroot = findParent(parent, y);

  if (rank[xroot] < rank[yroot]) {
    parent[xroot] = yroot;
  } else if (rank[xroot] > rank[yroot]) {
    parent[yroot] = xroot;
  } else {
    parent[yroot] = xroot;
    rank[xroot]++;
  }
}

anikanov::List< anikanov::List< int > > anikanov::runKruskalMST(List< List< int > > &edges, int V)
{
  List< List< int > > result;

  edges.sort([](List< int > a, List< int > b){
    return a[2] < b[2];
  });

  List< int > parent;
  for (int i = 0; i < V; ++i){
    parent.push_back(0);
  }
  List< int > rank(V, 0);

  for (int v = 0; v < V; ++v) {
    parent[v] = v;
  }

  for (auto &edge: edges) {
    int x = findParent(parent, edge[0]);
    int y = findParent(parent, edge[1]);

    if (x != y) {
      result.push_back(edge);
      merge(parent, rank, x, y);
    }
  }

  return result;
}

int anikanov::findNumberOfVertices(List< List< int > > &edges)
{
  List< int > vertices;

  for (auto &edge: edges) {
    vertices.push_back(edge[0]);
    vertices.push_back(edge[1]);
  }

  std::sort(vertices.begin(), vertices.end());
  vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());

  return vertices.size();
}

anikanov::List< anikanov::List< int > > anikanov::toMatrix(List< List< int > > &edges)
{
  int n = findNumberOfVertices(edges);
  List< List< int > > matrix;
  for (int i = 0; i < n; ++i){
    matrix.push_back(List< int >(n, 0));
  }

  for (auto &edge: edges) {
    matrix[edge[0]][edge[1]] = edge[2];
    matrix[edge[1]][edge[0]] = edge[2];
  }

  return matrix;
}

void anikanov::printAns(matrix_t &edges, const int sum, const std::shared_ptr< SceneManager > &manager)
{
  std::ostream *out = &manager->getOutputStream();
  std::ofstream fileOut;

  if (manager->getSettings().saveOutput) {
    fileOut = std::ofstream("out.txt");
    if (!fileOut.is_open()) {
      *out << "Error on opening file.\n";
      return;
    }
  }

  List< List< int > > toPrint = manager->getSettings().outputMatrix ? toMatrix(edges) : edges;

  for (auto &row: toPrint) {
    for (auto &elem: row) {
      *out << elem << " ";
      if (manager->getSettings().saveOutput) {
        fileOut << elem << " ";
      }
    }
    *out << "\n";
    if (manager->getSettings().saveOutput) {
      fileOut << "\n";
    }
  }

  *out << "\nMin sum:  " << sum << "\n";
  if (manager->getSettings().saveOutput) {
    fileOut << "\nMin sum:  " << sum;
  }

  fileOut.close();
}
