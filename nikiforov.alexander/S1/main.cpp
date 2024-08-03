#include "functions.hpp"

int main()
{
  using namespace nikiforov;

  using list_ull = List< std::pair< std::string, List< unsigned long long > > >;
  try
  {
    list_ull seqsPair;
    list_ull::Iterator iterSeqsPair = seqsPair.begin();
    std::string elemSeq = "";
    while (std::cin >> elemSeq)
    {
      if (isdigit(elemSeq[0]))
      {
        (*iterSeqsPair).second.push_back(std::stoull(elemSeq));
      }
      else
      {
        seqsPair.push_back({ elemSeq,{} });
        seqsPair.getSize() == 1 ? iterSeqsPair = seqsPair.begin() : iterSeqsPair++;
      }
    }

    size_t maxSize = 0;
    maxSize = outputName_(seqsPair);
    if (maxSize != 0)
    {
      List< unsigned long long > listSumm;
      outputSeqs_(seqsPair, listSumm, maxSize);
      outputSumm_(listSumm);
    }
    else
    {
      std::cout << 0 << "\n";
    }
  }
  catch (const std::overflow_error& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 0;
  }
  return 0;
}
