#include <iostream>
#include <string>
#include <limits>
#include <list.hpp>
#include <iterator.hpp>

int main()
{
  sobolevsky::List< sobolevsky::List< unsigned long long > > list;

  size_t maxlen = 0;
  size_t currlen = 0;
  size_t length = 0;
  std::string elem;
  bool isOverflow = false;
  while (std::cin >> elem)
  {
    if (isalpha(elem[0]))
    {
      maxlen = std::max(maxlen, currlen);
      sobolevsky::List< unsigned long long > subList;
      currlen = 0;
      list.pushBack(subList, elem);
      length++;
    }
    else
    {
      unsigned long long i = stoull(elem);
      currlen++;
      list.tail->data.pushBack(i, " ");
    }
  }

  if (length == 0)
  {
    std::cout << "0\n";
    return 0;
  }

  sobolevsky::BidirectionalIterator< sobolevsky::List< unsigned long long > > iter(list.head);
  for (size_t i = 0; i < length; i++)
  {
    std::cout << iter.name();
    ++iter;
    if (i != (length - 1))
    {
      std::cout << " ";
    }
  }
  std::cout << "\n";

  if (maxlen > 0)
  {
    sobolevsky::List< unsigned long long > lastList;
    size_t sumInts = 0;
    for (size_t i = 0; i < maxlen; i++)
    {
      sumInts = 0;
      bool first = true;
      sobolevsky::BidirectionalIterator< sobolevsky::List< unsigned long long > > iter2(list.head);
      for (size_t j = 0; j < length; j++)
      {
        if (i < iter2.currNode->data.getSize())
        {
          if (first)
          {
            std::cout << iter2.currNode->data[i]->data;
            first = false;
          }
          else
          {
            std::cout << " " << iter2.currNode->data[i]->data;
          }

          if (iter2.currNode->data[i]->data > (std::numeric_limits< unsigned long long >::max() - sumInts))
          {
            isOverflow = true;
          }
          else
          {
            sumInts += iter2.currNode->data[i]->data;
          }
        }
        ++iter2;
      }
      lastList.pushBack(sumInts, " ");
      std::cout << "\n";
    }

    if (isOverflow)
    {
      std::cerr << "Number is too big\n";
      return 1;
    }

    for (size_t i = 0; i < lastList.getSize(); i++)
    {
      std::cout << lastList[i]->data;
      if (i != (lastList.getSize() - 1))
      {
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  else
  {
    std::cout << "0\n";
  }

  return 0;
}
