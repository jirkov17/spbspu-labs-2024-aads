#ifndef ACTUALGRAPH_HPP
#define ACTUALGRAPH_HPP
#include <string>
#include "graph.hpp"
#include "BST.hpp"

namespace sukacheva
{
  struct ActualGraph
  {
    ActualGraph(Graph actualGraph_): actualGraph(actualGraph_), activityFlag(false) {}
    ~ActualGraph() = default;
    Graph actualGraph;
    bool activityFlag;
  };

  struct GraphList
  {
    GraphList() = default;
    ~GraphList() = default;
    BST< std::string, ActualGraph > graphList;
    Graph& findActiveWorkspace();
    Graph& findGraphName(std::string& name);
    Graph& switchActualGraph(std::string& name);
  };
}

#endif
