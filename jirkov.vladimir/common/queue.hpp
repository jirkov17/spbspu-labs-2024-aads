#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"

namespace jirkov
{
  template< typename T >
  class Queue
  {
  public:
    Queue() = default;
    Queue(const Queue< T >& otherQueue);
    Queue(Queue< T >&& otherQueue);
    ~Queue() = default;

    void push(const T& data);
    void drop();
    T& front();
    T& back();
    size_t getSize() const;
    bool isEmpty() const noexcept;

  private:
    List< T > queue;
  };
}

template< typename T >
jirkov::Queue< T >::Queue(const Queue< T >& otherQueue)
{
  queue(otherQueue.queue);
}

template< typename T >
jirkov::Queue< T >::Queue(Queue< T >&& otherQueue)
{
  queue(std::move(otherQueue.queue));
}

template< typename T >
void jirkov::Queue< T >::push(const T& data)
{
  queue.pushBack(data);
}

template< typename T >
void jirkov::Queue< T >::drop()
{
  queue.popFront();
}

template< typename T >
T& jirkov::Queue< T >::front()
{
  return queue.front();
}

template< typename T >
T& jirkov::Queue< T >::back()
{
  return queue.back();
}

template< typename T >
size_t jirkov::Queue< T >::getSize() const
{
  return queue.getSize();
}

template< typename T >
bool jirkov::Queue< T >::isEmpty() const noexcept
{
  return queue.isEmpty();
}

#endif
