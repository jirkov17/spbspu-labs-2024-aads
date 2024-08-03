#ifndef Node_HPP
#define Node_HPP
#include <utility>
#include <stdexcept>

namespace zasulsky
{
  namespace detail
  {
    template < class T >
    struct Node
    {
      Node()
      {
        next = nullptr;
      }

      Node(T data, Node< T >* next = nullptr)
      {
        this->data = data;
        this->next = next;
      }

      T data;
      Node< T >* next;
    };
  }
}
#endif
