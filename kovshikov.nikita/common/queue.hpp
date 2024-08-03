#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <doublelist.hpp>

namespace kovshikov
{
  template< typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >& q);
    Queue(Queue< T >&& q);
    ~Queue() = default;

    void push(const T& val);
    void pop();

    T& front() const;
    T& back() const;

    size_t getSize() const;
    bool isEmpty() const noexcept;

  private:
    DoubleList< T > queue;
  };
}

template< typename T >
kovshikov::Queue< T >::Queue(const Queue< T >& q)
{
  queue = q.queue;
}

template< typename T >
kovshikov::Queue< T >::Queue(Queue< T >&& q)
{
  queue = std::move(q.queue);
}

template< typename T >
void kovshikov::Queue< T >::push(const T& val)
{
  queue.pushBack(val);
}

template< typename T >
void kovshikov::Queue< T >::pop()
{
  queue.popFront();
}

template< typename T >
T& kovshikov::Queue< T >::front() const
{
  return queue.front();
}

template< typename T >
T& kovshikov::Queue< T >::back() const
{
  return queue.back();
}

template< typename T >
size_t kovshikov::Queue< T >::getSize() const
{
  size_t size = 0;
  typename DoubleList< T >::Iterator start = queue.begin();
  typename DoubleList< T >::Iterator finish = queue.end();
  while(start != finish)
  {
    size += 1;
    start++;
  }
  return size;
}

template< typename T >
bool kovshikov::Queue< T >::isEmpty() const noexcept
{
  return queue.empty();
}

#endif
