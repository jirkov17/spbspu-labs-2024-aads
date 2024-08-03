#ifndef NODE_HPP
#define NODE_HPP

namespace kovshikov
{
  namespace details
  {
    template< typename T >
    struct Node
    {
      Node():
        data(0),
        prev(nullptr),
        next(nullptr)
      {};
      Node(T data_):
        data(data_),
        prev(nullptr),
        next(nullptr)
      {};
      ~Node() = default;

      T data;
      Node* prev;
      Node* next;
    };
  }
}

#endif
