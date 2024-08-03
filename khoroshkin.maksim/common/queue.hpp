#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "list.hpp"

namespace khoroshkin
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue & rhs);
    Queue(Queue && rhs);
    ~Queue();

    Queue< T > & operator=(const Queue & rhs);
    Queue< T > & operator=(Queue && rhs);

    T & front() noexcept;
    const T & front() const noexcept;
    T & back() noexcept;
    const T & back() const noexcept;

    bool isEmpty() const;
    size_t getSize() const;

    void push(const T & value);
    void pop();
  private:
    List< T > queue;
  };
}

template< typename T >
khoroshkin::Queue< T >::Queue() :
  queue(List< T >())
{}

template< typename T >
khoroshkin::Queue< T >::Queue(const Queue & rhs)
{
  queue = rhs.queue;
}

template< typename T >
khoroshkin::Queue< T >::Queue(Queue && rhs) :
  queue(std::move(rhs.queue))
{}

template< typename T >
khoroshkin::Queue< T > & khoroshkin::Queue< T >::operator=(const Queue & rhs)
{
  queue = rhs.queue;
  return *this;
}

template< typename T >
khoroshkin::Queue< T > & khoroshkin::Queue< T >::operator=(Queue && rhs)
{
  queue = std::move(rhs.queue);
  return *this;
}

template< typename T >
khoroshkin::Queue< T >::~Queue()
{
  queue.clear();
}

template< typename T >
T & khoroshkin::Queue< T >::front() noexcept
{
  return queue.front();
}

template< typename T >
const T & khoroshkin::Queue< T >::front() const noexcept
{
  return queue.front();
}

template< typename T >
T & khoroshkin::Queue< T >::back() noexcept
{
  for (auto it = queue.begin(); it != queue.end(); it++)
  {
    if (next(it) == queue.end())
    {
      return *it;
    }
  }
  return *queue.begin();
}

template< typename T >
const T & khoroshkin::Queue< T >::back() const noexcept
{
  for (auto it = queue.begin(); it != queue.end(); it++)
  {
    if (next(it) == queue.end())
    {
      return *it;
    }
  }
  return *queue.begin();
}

template< typename T >
bool khoroshkin::Queue< T >::isEmpty() const
{
  return queue.isEmpty();
}

template< typename T >
size_t khoroshkin::Queue< T >::getSize() const
{
  return queue.getSize();
}

template< typename T >
void khoroshkin::Queue< T >::push(const T & value)
{
  try
  {
    queue.push_back(value);
  }
  catch(const std::bad_alloc & e)
  {
    queue.clear();
    throw e;
  }
}

template< typename T >
void khoroshkin::Queue< T >::pop()
{
  queue.pop_front();
}

#endif
