#ifndef COMMANDSTRAVERSE_HPP
#define COMMANDSTRAVERSE_HPP
#include <commands.hpp>

namespace nikiforov
{
  void createTree(std::string& strVocab, AvlTree< long long, std::string >& dict);

  void lnrTraverse(AvlTree< long long, std::string >& traversalTree, std::ostream& out);

  void rnlTraverse(AvlTree< long long, std::string>& traversalTree, std::ostream& out);

  void breadthTraverse(AvlTree< long long, std::string>& traversalTree, std::ostream& out);
}
#endif
