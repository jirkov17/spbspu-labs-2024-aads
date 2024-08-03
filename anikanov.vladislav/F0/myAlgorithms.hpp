#ifndef MYALGORITHMS_HPP
#define MYALGORITHMS_HPP

#include <list.hpp>
#include <memory>
#include "sceneManager.hpp"

namespace anikanov {
  using matrix_t = List< List< int > >;
  bool checkMatrix(List< List< int > > &matrix);
  List< List< int > > getEdges(List< List< int > > &graph);
  int findNumberOfVertices(List< List< int > > &edges);
  List< List< int > > toMatrix(List< List< int > > &edges);
  void printAns(matrix_t &edges, const int sum, const std::shared_ptr<SceneManager> &manager);

  int findParent(List< int > &parent, int i);
  List< List< int > > runKruskalMST(List< List< int > > &edges, int V);
  void merge(List< int > &parent, List< int > &rank, int x, int y);
}

#endif
