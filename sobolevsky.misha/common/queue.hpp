#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <utility>
#include <stdexcept>
#include <list.hpp>

namespace sobolevsky
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue& rhs) noexcept;
    Queue(Queue&& rhs);
    ~Queue();

    void push(T data);
    T back();
    void pop();
    bool empty();
    long long size();
  private:
    List< T > list;
  };
}

template< typename T >
sobolevsky::Queue< T >::Queue()
{
  list = List< T >();
}

template< typename T >
sobolevsky::Queue< T >::Queue(const Queue& rhs) noexcept
{
  list = rhs.list;
}

template< typename T >
sobolevsky::Queue< T >::Queue(Queue&& rhs)
{
  list = std::move(rhs.list);
}

template< typename T >
sobolevsky::Queue< T >::~Queue()
{
  list.clear();
}

template< typename T >
void sobolevsky::Queue< T >::push(T data)
{
  list.pushBack(data, "");
}

template< typename T >
T sobolevsky::Queue< T >::back()
{
  if (list[0] == nullptr)
  {
    throw std::logic_error("stack is empty");
  }
  return list[0]->data;
}

template< typename T >
void sobolevsky::Queue< T >::pop()
{
  list.popFront();
}

template< typename T >
bool sobolevsky::Queue< T >::empty()
{
  return (list.empty());
}

template< typename T >
long long sobolevsky::Queue< T >::size()
{
  return list.getSize();
}

#endif
