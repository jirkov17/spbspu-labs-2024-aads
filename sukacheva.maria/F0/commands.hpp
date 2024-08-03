#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "graph.hpp"
#include "ActualGraph.hpp"

namespace sukacheva
{
  void help(std::ostream& out);
  void capacity(GraphList& graphList, std::istream& in, std::ostream& out);
  void graphName(GraphList& graphList, std::ostream& out);
  void clearGraph(GraphList& graphList, std::ostream& out);
  void printGraphList(std::ostream& out, GraphList graphList);
  void printMatrix(GraphList& graphList, std::ostream& out);
  void commandCreateGraph(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandAdd(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandPrint(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandDelete(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandSwitch(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandOpen(GraphList& graphList, std::istream& in, std::ostream& out);
  void commandSave(GraphList& graphList, std::istream& in, std::ostream& out);
}

#endif
