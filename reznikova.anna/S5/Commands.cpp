#include "Commands.hpp"
#include "TreeProcessing.hpp"
#include "TraverseObject.hpp"

void reznikova::ascendingCommand(Tree< int, std::string > & tree)
{
  if (tree.isEmpty())
  {
    outputEmptyError(std::cout);
    return;
  }
  Traverse operation;
  try
  {
    Traverse result = tree.traverse_lnr(operation);
    output(result);
  }
  catch (std::exception & e)
  {
    throw std::runtime_error(e.what());
  }
}

void reznikova::descendingCommand(Tree< int, std::string > & tree)
{
  if (tree.isEmpty())
  {
    outputEmptyError(std::cout);
    return;
  }
  Traverse operation;
  try
  {
    Traverse result = tree.traverse_rnl(operation);
    output(result);
  }
  catch (std::exception & e)
  {
    throw std::runtime_error(e.what());
  }
}

void reznikova::breadthCommand(Tree< int, std::string > & tree)
{
  if (tree.isEmpty())
  {
    outputEmptyError(std::cout);
    return;
  }
  Traverse operation;
  try
  {
    Traverse result = tree.traverse_breadth(operation);
    output(result);
  }
  catch (std::exception & e)
  {
    throw std::runtime_error(e.what());
  }
}

