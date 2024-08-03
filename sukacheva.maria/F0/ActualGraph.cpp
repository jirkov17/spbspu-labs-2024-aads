#include "ActualGraph.hpp"
#include <stdexcept>
#include <algorithm>

namespace sukacheva
{
  Graph& sukacheva::GraphList::findActiveWorkspace()
  {
    for (auto it = graphList.begin(); it != graphList.end(); ++it)
    {
      if (it->second.activityFlag)
      {
        return it->second.actualGraph;
      }
    }
    throw std::logic_error("No active workspace found.\n");
  }

  Graph& sukacheva::GraphList::findGraphName(std::string& name)
  {
    for (auto it = graphList.begin(); it != graphList.end(); ++it)
    {
      if (it->first == name)
      {
        return it->second.actualGraph;
      }
    }
    throw std::logic_error("Graph with the specified name not found.\n");
  }

  Graph& sukacheva::GraphList::switchActualGraph(std::string& name)
  {
    for (auto it = graphList.begin(); it != graphList.end(); ++it)
    {
      if (it->second.activityFlag)
      {
        it->second.activityFlag = false;
        break;
      }
    }
    for (auto it = graphList.begin(); it != graphList.end(); ++it)
    {
      if (it->first == name)
      {
        it->second.activityFlag = true;
        return it->second.actualGraph;
      }
    }
    throw std::logic_error("Graph with the specified name not found.\n");
  }
}
