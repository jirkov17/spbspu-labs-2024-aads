#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <List.hpp>

namespace reznikova
{
  template< typename T >
  class Queue
  {
  public:
    Queue();
    Queue(const Queue & other);
    Queue(Queue && other);
    ~Queue() = default;
    void push(const T & value);
    void pop();
    bool empty() noexcept;
    T & getValue() const noexcept;
    size_t getSize() const noexcept;
    void reverse();
  private:
    List< T > data_;
  };
}

template< typename T >
reznikova::Queue< T >::Queue():
  data_(List< T >())
{}

template< typename T >
reznikova::Queue< T >::Queue(const Queue & other):
  data_(other.data_)
{}

template< typename T >
reznikova::Queue< T >::Queue(Queue && other):
  data_(other.data_)
{
    other.data_.clear();
}

template< typename T >
void reznikova::Queue< T >::push(const T & value)
{
  data_.pushBack(value);
}

template< typename T >
void reznikova::Queue< T >::pop()
{
  data_.popFront();
}

template< typename T >
bool reznikova::Queue< T >::empty() noexcept
{
  return data_.empty();
}

template< typename T >
T & reznikova::Queue< T >::getValue() const noexcept
{
  return data_.getFront();
}

template< typename T >
size_t reznikova::Queue< T >::getSize() const noexcept
{
  return data_.getSize();
}

template< typename T >
void reznikova::Queue< T >::reverse()
{
  return data_.reverse();
}

#endif
