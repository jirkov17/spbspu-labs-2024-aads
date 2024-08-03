#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cassert>
#include <iostream>
#include <list.hpp>

namespace anikanov {

  template< typename T >
  class Queue {
  public:
    Queue() = default;
    Queue(const Queue &rhs);
    Queue(Queue &&rhs) noexcept;
    ~Queue() = default;

    Queue &operator=(const Queue &rhs) noexcept;
    Queue &operator=(Queue &&rhs) noexcept;

    T &front() noexcept;
    const T &front() const noexcept;
    T &back() noexcept;
    const T &back() const noexcept;

    bool isEmpty() const noexcept;
    size_t getSize() const;

    void push(const T &value);
    void pop();
  private:
    List< T > list;
  };
}

template< typename T >
anikanov::Queue< T >::Queue(const Queue &rhs)
{
  list = rhs.list;
}

template< typename T >
anikanov::Queue< T >::Queue(Queue &&rhs) noexcept
{
  list = std::move(rhs.list);
}

template< typename T >
anikanov::Queue< T > &anikanov::Queue< T >::operator=(const Queue &rhs) noexcept
{
  if (this == &rhs) {
    return *this;
  }
  list.clear();
  for (auto elem: rhs.list) {
    list.push_back(elem);
  }
  return *this;
}

template< typename T >
anikanov::Queue< T > &anikanov::Queue< T >::operator=(Queue &&rhs) noexcept
{
  if (this == &rhs) {
    return *this;
  }
  list.clear();
  for (auto elem: rhs.list) {
    list.push_back(elem);
  }
  return *this;
}

template< typename T >
T &anikanov::Queue< T >::front() noexcept
{
  assert(!list.empty());
  return list[0];
}

template< typename T >
const T &anikanov::Queue< T >::front() const noexcept
{
  assert(!list.empty());
  return list[0];
}

template< typename T >
T &anikanov::Queue< T >::back() noexcept
{
  assert(!list.empty());
  return list[list.size() - 1];
}

template< typename T >
const T &anikanov::Queue< T >::back() const noexcept
{
  assert(!list.empty());
  return list[list.size() - 1];
}

template< typename T >
bool anikanov::Queue< T >::isEmpty() const noexcept
{
  return list.empty();
}

template< typename T >
size_t anikanov::Queue< T >::getSize() const
{
  return list.size();
}

template< typename T >
void anikanov::Queue< T >::push(const T &value)
{
  list.push_back(value);
}

template< typename T >
void anikanov::Queue< T >::pop()
{
  assert(!list.empty());
  list.pop(0);
}

#endif
