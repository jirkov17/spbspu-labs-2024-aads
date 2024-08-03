#include "Vertex.hpp"
#include <algorithm>

bool reznikova::Vertex::isRelated(size_t vertex) const
{
  for (const auto& vertexToCmp : relatedVertices_)
  {
    if (vertexToCmp->index_ == vertex)
    {
      return true;
    }
  }
  return false;
}

void reznikova::Vertex::add(Vertex * vertex)
{
  if (isRelated(vertex->index_)) {
    throw std::logic_error("can't add edge which exists\n");
  }
  relatedVertices_.pushBack(vertex);
}

void reznikova::Vertex::remove(Vertex * vertex)
{
    relatedVertices_.remove(vertex);
}

std::size_t reznikova::Vertex::getIndex()
{
  return index_;
}
