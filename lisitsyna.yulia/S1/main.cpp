#include <iostream>
#include "sequences_funcs.hpp"

int main()
{
  size_t maxLen = 0;
  auto sequences = readSequences(maxLen, std::cin);

  outSequencesName(sequences, std::cout);
  if (sequences.empty())
  {
    std::cout << 0 << '\n';
    return 0;
  }
  std::cout << '\n';

  outSequencesValues(sequences, maxLen, std::cout);

  List< unsigned long long > sums;
  try
  {
    sums = sumSequencesValues(sequences, maxLen);
  }
  catch (const std::overflow_error & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  outSequence(sums, std::cout);

  if (sums.empty())
  {
    std::cout << '0';
  }
  std::cout << '\n';
  return 0;
}
