#ifndef LIST_ITEM_HPP
#define LIST_ITEM_HPP
namespace zheleznyakov
{
  namespace details
  {
    template < typename T >
    class Node
    {
    public:
      Node(T value, Node< T > *next = nullptr, Node< T > *prev = nullptr);
      T value;
      Node< T > *next;
      Node< T > *prev;
    };
  }
}

template < typename T >
zheleznyakov::details::Node< T >::Node(T value, Node< T > *next, Node< T >*prev):
  value(value),
  next(next),
  prev(prev)
{
}
#endif
