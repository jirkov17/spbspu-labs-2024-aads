#include "utilsForDictsAndErrors.hpp"

void sobolevsky::error(std::ostream & out)
{
  out << "ERROR: INVALID COMMAND\n";
}

void sobolevsky::errorInpName(std::ostream & out)
{
  out << "ERROR: SOMETHING WITH FILE NAME/SOMETHING WITH DICT NAME\n";
}

bool sobolevsky::isNameHere(mypair &pair, const std::string &name)
{
  return pair.first == name;
}

void sobolevsky::dictOutput(mypair &myPair, std::ostream & out, size_t n, bool mode)
{
  size_t i = 0;
  for (MyMultiMap< size_t, std::string >::Iterator iter = myPair.second.rbegin(); iter != myPair.second.end(); iter--)
  {
    if (iter->size() == 1)
    {
      i++;
      out << (*iter)[0];
      if (mode)
      {
        out << " " << iter.getKey();
      }
      out << "\n";
      if (i == n)
      {
        break;
      }
    }
    else
    {
      for (size_t j = 0; j < iter->size(); j++)
      {
        i++;
        out << (*iter)[j];
        if (mode)
        {
          out << " " << iter.getKey();
        }
        out << "\n";
        if (i == n)
        {
          break;
        }
      }
    }
  }
}

char sobolevsky::charCheck(char in)
{
  if (in <= 'Z' && in >= 'A')
  {
    return in - ('Z' - 'z');
  }
  else if (in <= 'z' && in >= 'a')
  {
    return in;
  }
  else
  {
    return 0;
  }
}

typename sobolevsky::List< mypair >::Iterator sobolevsky::findIf(typename sobolevsky::List< mypair >::Iterator &&first,
typename sobolevsky::List< mypair >::Iterator &&last, std::string &name)
{
  List< mypair >::Iterator iterFirst(first);
  List< mypair >::Iterator iterLast(last);
  while (iterFirst != iterLast)
  {
    if (isNameHere(*iterFirst, name))
    {
      return iterFirst;
    }
    iterFirst++;
  }
  return iterFirst;
}
