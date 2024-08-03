#include "commands.hpp"
#include "keySumm.hpp"

void sobolevsky::ascending(std::ostream &out, const sobolevsky::AVLtree< long long, std::string, long long > &tree)
{
  Key_summ keySumm;
  keySumm = tree.traverse_lnr< Key_summ >(keySumm);
  out << keySumm.getKeyResult() << keySumm.getValueResult() << "\n";
}

void sobolevsky::descending(std::ostream &out, const sobolevsky::AVLtree< long long, std::string, long long > &tree)
{
  Key_summ keySumm;
  keySumm = tree.traverse_rnl< Key_summ >(keySumm);
  out << keySumm.getKeyResult() << keySumm.getValueResult() << "\n";
}

void sobolevsky::breadth(std::ostream &out, const sobolevsky::AVLtree< long long, std::string, long long > &tree)
{
  Key_summ keySumm;
  keySumm = tree.traverse_breadth< Key_summ >(keySumm);
  out << keySumm.getKeyResult() << keySumm.getValueResult() << "\n";
}
