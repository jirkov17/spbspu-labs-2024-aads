#include "traverseFuncs.hpp"
#include <iostream>
#include "functionalObject.hpp"

void khoroshkin::ascendingTraverse(const Tree< int, std::string > & data, std::ostream & out)
{
  Traverse functor{};
  try
  {
    Traverse result = data.traverse_lnr(functor);
    outFunctor(out, result);
  }
  catch(const std::exception & e)
  {
    throw e;
  }
}

void khoroshkin::descendingTraverse(const Tree< int, std::string > & data, std::ostream & out)
{
  Traverse functor{};
  try
  {
    Traverse result = data.traverse_rnl(functor);
    outFunctor(out, result);
  }
  catch(const std::exception & e)
  {
    throw e;
  }
}

void khoroshkin::breadthTraverse(const Tree< int, std::string > & data, std::ostream & out)
{
  Traverse functor{};
  try
  {
    Traverse result = data.traverse_breadth(functor);
    outFunctor(out, result);
  }
  catch(const std::exception & e)
  {
    throw e;
  }
}

void khoroshkin::outFunctor(std::ostream & out, Traverse & functor)
{
  out << functor.result << " ";
  while (!functor.bypass.isEmpty())
  {
    out << functor.bypass.front();
    out << ((functor.bypass.front() == functor.bypass.back()) ? "\n" : " ");
    functor.bypass.pop();
  }
}
