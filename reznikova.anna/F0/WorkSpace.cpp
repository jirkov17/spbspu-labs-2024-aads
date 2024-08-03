#include "WorkSpace.hpp"
#include <iterator>
#include <vector>
#include <functional>
#include <algorithm>

bool reznikova::GraphList::isGraphInList(std::string graphName) const
{
  for (const auto& graphToCmp : graphList_)
  {
    if (graphToCmp->graph_.getGraphName() == graphName)
    {
      return true;
    }
  }
  return false;
}

void reznikova::WorkObject::resetFlag()
{
  isActive_ = false;
}

void reznikova::GraphList::addToList(reznikova::Graph graph)
{
  if (isGraphInList(graph.getGraphName()))
  {
    throw std::logic_error("this graph is already exists\n");
  }
  resetActiveFlags();
  graphList_.pushBack(new WorkObject(graph));
}

void reznikova::GraphList::resetActiveFlags()
{
  auto it = graphList_.begin();
  while (it != graphList_.end())
  {
    it.node_->data_->resetFlag();
  }
}

reznikova::WorkObject* reznikova::GraphList::findGraphByName(std::string graphName) const
{
  for (const auto & objToCmp : graphList_)
  {
    if (objToCmp->graph_.getGraphName() == graphName)
    {
      return objToCmp;
    }
  }
  return nullptr;
}

reznikova::WorkObject* reznikova::GraphList::getActiveGraph()
{
  if (graphList_.empty())
  {
    throw std::logic_error("You did not add any graph\n");
  }
  for (const auto & objToCmp : graphList_)
  {
    if (objToCmp->isActive_)
    {
      return objToCmp;
    }
  }
  throw std::logic_error("No active graph found\n");
}
