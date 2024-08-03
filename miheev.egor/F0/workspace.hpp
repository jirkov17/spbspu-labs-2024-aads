#ifndef WORKSPACE_HPP
#define WORKSPACE_HPP

#include "graph.hpp"

namespace miheev
{
  struct Workspace
  {
    Tree< std::string, Graph > graphs;
    Graph current;
    bool isActive;
  };
}

#endif
