#ifndef QUEUE_HPP
#define QUEUE_HPP
#include "list.hpp"

namespace redko
{
  template < typename T >
  class Queue {
  public:
    Queue(): container_(List< T >()) {}
    explicit Queue(const List< T > & cont);
    Queue(const Queue & other);
    Queue(Queue && other);
    ~Queue() = default;

    Queue< T > & operator=(const Queue & other);
    Queue< T > & operator=(Queue && other);

    T & front();
    const T & front() const;
    T & back();
    const T & back() const;

    bool empty() const;
    size_t size() const;

    void push(const T & value);
    void push(T && value);
    void pop();
    void swap(Queue & other) noexcept;

  private:
    List< T > container_;
  };
}

template < typename T >
redko::Queue< T >::Queue(const List< T > & cont):
  container_(cont)
{}

template < typename T >
redko::Queue< T >::Queue(const Queue & other):
  container_(other.container_)
{}

template < typename T >
redko::Queue< T >::Queue(Queue && other):
  container_(std::move(other.container_))
{}

template < typename T >
redko::Queue< T > & redko::Queue< T >::operator=(const Queue & other)
{
  container_ = other.container_;
  return *this;
}

template < typename T >
redko::Queue< T > & redko::Queue< T >::operator=(Queue && other)
{
  container_ = std::move(other.container_);
  return *this;
}

template < typename T >
T & redko::Queue< T >::front()
{
  return container_.front();
}

template < typename T >
const T & redko::Queue< T >::front() const
{
  return container_.front();
}

template < typename T >
T & redko::Queue< T >::back()
{
  if (container_.isEmpty())
  {
    throw std::logic_error("Error: empty container");
  }
  typename List< T >::iterator curr = container_.begin();
  typename List< T >::iterator next = ++curr;
  while (next != container_.end())
  {
    ++curr;
    ++next;
  }
  return (*curr);
}

template < typename T >
const T & redko::Queue< T >::back() const
{
  if (container_.isEmpty())
  {
    throw std::logic_error("Error: empty container");
  }
  typename List< T >::iterator curr = container_.begin();
  typename List< T >::iterator next = ++curr;
  while (next != container_.end())
  {
    ++curr;
    ++next;
  }
  return (*curr);
}

template < typename T >
bool redko::Queue< T >::empty() const
{
  return container_.isEmpty();
}

template < typename T >
size_t redko::Queue< T >::size() const
{
  size_t size = 0;
  typename List< T >::iterator curr = container_.begin();
  while (curr != container_.end())
  {
    ++size;
    ++curr;
  }
  return size;
}

template < typename T >
void redko::Queue< T >::push(const T & value)
{
  container_.pushBack(value);
}

template < typename T >
void redko::Queue< T >::push(T && value)
{
  container_.pushBack(std::move(value));
}

template < typename T >
void redko::Queue< T >::pop()
{
  container_.popFront();
}

template < typename T >
void redko::Queue< T >::swap(Queue & other) noexcept
{
  container_.swap(other.container_);
}

#endif
