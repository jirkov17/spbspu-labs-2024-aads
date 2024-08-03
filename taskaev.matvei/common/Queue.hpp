#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "List.hpp"

namespace taskaev
{
  template < typename T >
  class Queue
  {
  public:
    Queue();
    Queue(Queue< T >&& other);
    Queue(const Queue< T >& other);
    ~Queue() = default;
    void push(const T& value);
    void pop();
    bool isEmpty() const noexcept;
    T& front();
  private:
    List< T > container_;
  };
}

template< typename T >
taskaev::Queue< T >::Queue():
  container_(List< T >())
{}

template< typename T >
taskaev::Queue< T >::Queue(const Queue< T >& other):
  container_(other)
{}

template< typename T >
taskaev::Queue< T >::Queue(Queue< T >&& other):
  container_(other.container_)
{}

template < typename T >
void taskaev::Queue< T >::push(const T& value)
{
  container_.pushBack(value);
}

template < typename T >
void taskaev::Queue< T >::pop()
{
  container_.popFront();
}

template < typename T >
bool taskaev::Queue< T >::isEmpty() const noexcept
{
  return container_.isEmpty();
}

template < typename T >
T& taskaev::Queue< T >::front()
{
  return container_.front();
}

#endif
