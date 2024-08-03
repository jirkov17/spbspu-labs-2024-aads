#include "outputFunctions.hpp"
#include <limits>

std::ostream& redko::printElementsInOrder(std::ostream& out, const List< std::pair< std::string, List< unsigned long long > > > & list)
{
  List< std::pair< std::string, List< unsigned long long > > >::const_iterator currSeq = list.begin();
  bool allWasOutputed = false;
  size_t elemNum = 0;
  while (!allWasOutputed)
  {
    allWasOutputed = true;
    while (currSeq != list.end())
    {
      List< unsigned long long >::const_iterator currElem = currSeq->second.begin();
      size_t i = 0;
      while (i < elemNum && currElem != currSeq->second.end())
      {
        currElem++;
        i++;
      }
      if (currElem != currSeq->second.end())
      {
        out << *currElem;
        List< std::pair< std::string, List< unsigned long long > > >::const_iterator nextSeq = currSeq;
        bool isNext = false;
        while (nextSeq != list.end() && ++nextSeq != list.end() && !isNext)
        {
          size_t i = 0;
          List< unsigned long long >::const_iterator nextElem = nextSeq->second.begin();
          while (i < elemNum && nextElem != nextSeq->second.end())
          {
            nextElem++;
            i++;
          }
          if (nextElem != nextSeq->second.end())
          {
            isNext = true;
          }
        }
        out << (isNext ? ' ' : '\n');
        allWasOutputed = false;
      }
      currSeq++;
    }
    elemNum++;
    currSeq = list.begin();
  }
  return out;
}

redko::List< unsigned long long > * redko::calculateSums(List< std::pair< std::string, List< unsigned long long > > > & list)
{
  List< unsigned long long > * res = new List< unsigned long long >();
  List< unsigned long long >::iterator sumNum = res->beforeBegin();
  List< std::pair< std::string, List< unsigned long long > > >::iterator currSeq = list.begin();
  List< std::pair< std::string, List< unsigned long long > > >::iterator prevSeq = list.beforeBegin();
  while (!list.isEmpty())
  {
    res->pushBack(0);
    sumNum++;
    currSeq = list.begin();
    prevSeq = list.beforeBegin();

    while (currSeq != list.end())
    {
      if (!(currSeq->second.isEmpty()))
      {
        if (*(currSeq->second.begin()) > std::numeric_limits< unsigned long long >::max() - *sumNum)
        {
          delete res;
          throw std::overflow_error("Error: unable to calculate the sum due to overflow");
        }
        *sumNum += *(currSeq->second.begin());
        currSeq->second.popFront();
        if (currSeq->second.isEmpty())
        {
          currSeq = list.eraseAfter(prevSeq);
          currSeq++;
        }
        else
        {
          currSeq++;
          prevSeq++;
        }
      }
      else
      {
        currSeq = list.eraseAfter(prevSeq);
        currSeq++;
      }
    }
  }
  return res;
}
