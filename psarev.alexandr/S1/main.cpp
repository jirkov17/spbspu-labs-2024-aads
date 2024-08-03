#include "ioFuncs.hpp"

int main()
{
  using depot_t = psarev::List< std::pair< std::string, psarev::List< unsigned long long > > >;
  depot_t lines;
  size_t maxDigits = 0;

  psarev::inputData< unsigned long long >(lines, maxDigits);
  psarev::outOrds< unsigned long long >(lines);

  bool isOverflow = false;
  psarev::List< unsigned long long > sums = psarev::outDigits < unsigned long long >(lines, maxDigits, isOverflow);
  if (isOverflow)
  {
    std::cerr << "Error: Value overflow during counting the sum!\n";
    return 1;
  }
  psarev::outSums< unsigned long long >(sums);
  return 0;
}
