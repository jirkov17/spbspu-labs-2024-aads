#include <iostream>
#include <utility>
#include "list.hpp"
#include "inputFunctions.hpp"
#include "outputFunctions.hpp"

int main()
{
  using pair_list = redko::List< std::pair< std::string, redko::List< unsigned long long > > >;
  pair_list seqs{};
  pair_list::iterator currSeq = seqs.beforeBegin();
  unsigned long long value = 0;
  std::string seq;
  std::string name;
  while (!std::cin.eof())
  {
    std::getline(std::cin, seq);
    if (seq != "")
    {
      name = redko::cutName(seq);
      seqs.pushBack(std::pair< std::string, redko::List< unsigned long long > >(name, redko::List< unsigned long long >()));
      currSeq++;
      while (!seq.empty())
      {
        value = redko::cutValue(seq);
        currSeq->second.pushBack(value);
      }
    }
  }
  if (seqs.isEmpty())
  {
    std::cout << 0 << '\n';
  }
  else
  {
    currSeq = seqs.begin();
    while (currSeq != seqs.end())
    {
      std::cout << currSeq->first;
      currSeq++;
      std::cout << (currSeq == seqs.end() ? '\n' : ' ');
    }
    redko::printElementsInOrder(std::cout, seqs);

    redko::List< unsigned long long > * sums = nullptr;
    try
    {
      sums = redko::calculateSums(seqs);
    }
    catch (const std::overflow_error & e)
    {
      std::cerr << e.what() << '\n';
      return 1;
    }

    redko::List< unsigned long long >::iterator currSum = sums->begin();
    while (currSum != sums->end())
    {
      std::cout << *currSum;
      std::cout << (++currSum != sums->end() ? ' ' : '\n');
    }
    delete sums;
  }
  return 0;
}
