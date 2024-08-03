#ifndef NODE_HPP
#define NODE_HPP
#include <string>

namespace sobolevsky
{
  template< typename T >
  class Node
  {
  public:
    Node * next;
    Node * prev;
    T data;
    std::string name;

    Node(T dataIn, std::string nameIn);
  };
}

template< typename T >
sobolevsky::Node< T >::Node(T dataIn, std::string nameIn)
{
  data = dataIn;
  name = nameIn;
  prev = nullptr;
  next = nullptr;
}

#endif
