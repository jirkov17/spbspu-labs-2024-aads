#ifndef SHELL_SORT_HPP
#define SHELL_SORT_HPP
#include <iterator>
#include <cstddef>

namespace psarev
{
  template< typename Iter, typename Compare >
  void sortShell(Iter begin, Iter end, Compare compare);
}

template< typename Iter, typename Compare >
void psarev::sortShell(Iter begin, Iter end, Compare compare) {
  auto distance = std::distance(begin, end);

  for (size_t space = distance / 2; space > 0; space /= 2)
  {
    for (Iter i = std::next(begin, space); i != end; ++i)
    {
      auto tempo = *i;
      Iter j;
      for (j = i; j >= std::next(begin, space) && compare(tempo, *std::prev(j, space)); j = std::prev(j, space))
      {
        *j = *std::prev(j, space);
      }
      *j = tempo;
    }
  }
}

#endif
