#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <cstdlib>
#include <ctime>

namespace zheleznyakov
{
  namespace anarchy
  {
    double randomDouble()
    {
      return (rand() - rand()) % 1000 + (double(rand()) / rand());
    }
  }
}
#endif
