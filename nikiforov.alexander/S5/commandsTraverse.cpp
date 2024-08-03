#include "structSumm.hpp"
#include "commandsTraverse.hpp"

void nikiforov::createTree(std::string& strVocab, AvlTree< long long, std::string >& dict)
{
  std::string key;
  std::string value;

  while (!strVocab.empty())
  {
    key = cutElem(strVocab);
    value = cutElem(strVocab);
    dict.emplace(stoll(key), value);
  }
}

void nikiforov::lnrTraverse(AvlTree<long long, std::string>& traversalTree, std::ostream& out)
{
  if (!traversalTree.is_empty())
  {
    nikiforov::Key_summ keySumStruct;
    keySumStruct = traversalTree.traverse_lnr(keySumStruct);

    out << keySumStruct.result << keySumStruct.strValues << "\n";
  }
  else
  {
    emptyMessage(out);
  }
}

void nikiforov::rnlTraverse(AvlTree<long long, std::string>& traversalTree, std::ostream& out)
{
  if (!traversalTree.is_empty())
  {
    nikiforov::Key_summ keySumStruct;
    keySumStruct = traversalTree.traverse_rnl(keySumStruct);

    out << keySumStruct.result << keySumStruct.strValues << "\n";
  }
  else
  {
    emptyMessage(out);
  }
}

void nikiforov::breadthTraverse(AvlTree<long long, std::string>& traversalTree, std::ostream& out)
{
  if (!traversalTree.is_empty())
  {
    nikiforov::Key_summ keySumStruct;
    keySumStruct = traversalTree.traverse_breadth(keySumStruct);

    out << keySumStruct.result << keySumStruct.strValues << "\n";
  }
  else
  {
    emptyMessage(out);
  }
}
