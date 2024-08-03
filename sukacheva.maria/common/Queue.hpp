#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "List.hpp"

namespace sukacheva {
  template < typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue&);
    Queue(Queue&& other);
    ~Queue() = default;

    bool empty() const noexcept;
    size_t getSize() const noexcept;
    T& front() noexcept;
    const T& front() const noexcept;
    T& back() const noexcept;
    void push(const T& value);
    void push(T&& value);
    void pop();
    void swap(Queue& other) noexcept;

  private:
    List< T > container;
  };
}

template< typename T >
sukacheva::Queue< T >::Queue() :
  container(List< T >())
{}

template< typename T >
sukacheva::Queue< T >::Queue(const Queue& cont) :
  container(cont.container)
{}

template< typename T >
sukacheva::Queue< T >::Queue(Queue&& other) :
  container(other.container)
{
  other.container.clean();
}

template< typename T >
bool sukacheva::Queue< T >::empty() const noexcept
{
  return container.empty();
}

template< typename T >
size_t sukacheva::Queue< T >::getSize() const noexcept
{
  return container.getSize();
}

template< typename T >
T& sukacheva::Queue< T >::front() noexcept
{
  return container.front();
}

template< typename T >
const T& sukacheva::Queue< T >::front() const noexcept
{
  return container.front();
}

template< typename T >
T& sukacheva::Queue< T >::back() const noexcept
{
  return container.back();
}

template< typename T >
void sukacheva::Queue< T >::push(const T& value)
{
  container.pushBack(value);
}

template< typename T >
void sukacheva::Queue< T >::push(T&& value)
{
  container.pushBack(value);
}

template< typename T >
void sukacheva::Queue< T >::pop()
{
  container.popFront();
}

template< typename T >
void sukacheva::Queue< T >::swap(Queue& other) noexcept
{
  container.swap(other.container);
}

#endif
