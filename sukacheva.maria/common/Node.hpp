#ifndef NODE_HPP
#define NODE_HPP

namespace sukacheva {
  namespace details {
    template < typename T >
    struct Node
    {
      explicit Node(T data_) : data(data_), next(nullptr) {}
      T data;
      Node< T >* next;
    };
  }
}

#endif
