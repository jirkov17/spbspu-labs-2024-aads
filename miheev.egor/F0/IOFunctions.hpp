#ifndef IO_FUNCTIONS_HPP
#define IO_FUNCTIONS_HPP

#include "workspace.hpp"

namespace miheev
{
  void getGraphsNames(const Workspace&, List< std::string >&);
  void initWorkspace(int argc, char* argv[], Workspace& workspace);
  void readGraph(const std::string& filename, Graph& container);
  std::ostream& sendMessage(std::ostream&, const std::string&);
}

#endif
