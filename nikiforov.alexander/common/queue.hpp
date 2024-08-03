#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <list.hpp>

namespace nikiforov
{
  template < typename T >
  class Queue {
  public:
    Queue();
    Queue(const List< T >& other);
    Queue(const Queue& other);
    ~Queue() = default;

    T& front();
    T& back();

    bool is_empty() noexcept;
    size_t getSize();

    void push_back(const T& value);
    void pop_front();

  private:
    List< T > container_;
  };
}

template<typename T>
nikiforov::Queue<T>::Queue() :
  container_(List< T >())
{}

template < typename T >
nikiforov::Queue< T >::Queue(const List< T >& other) :
  container_(other)
{}

template < typename T >
nikiforov::Queue< T >::Queue(const Queue& other) :
  container_(other.container_)
{}

template < typename T >
T& nikiforov::Queue< T >::front()
{
  return container_.front();
}

template < typename T >
T& nikiforov::Queue< T >::back()
{
  return container_.back();
}

template < typename T >
bool nikiforov::Queue< T >::is_empty() noexcept
{
  return container_.is_empty();
}

template < typename T >
size_t nikiforov::Queue< T >::getSize()
{
  return container_.getSize();
}

template < typename T >
void nikiforov::Queue< T >::push_back(const T& value)
{
  container_.push_back(value);
}

template < typename T >
void nikiforov::Queue< T >::pop_front()
{
  container_.pop_front();
}

#endif
