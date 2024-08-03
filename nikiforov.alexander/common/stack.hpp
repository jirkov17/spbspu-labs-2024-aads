#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>

namespace nikiforov
{
  template < typename T >
  class Stack {
  public:
    Stack();
    Stack(const List< T >& other);
    Stack(const Stack& other);
    ~Stack() = default;

    T& back();

    bool is_empty() noexcept;
    size_t getSize();

    void push_back(const T& value);
    void pop_back();

  private:
    List< T > container_;
  };
}

template<typename T>
nikiforov::Stack<T>::Stack() :
  container_(List< T >())
{}

template < typename T >
nikiforov::Stack< T >::Stack(const List< T >& other) :
  container_(other)
{}

template < typename T >
nikiforov::Stack< T >::Stack(const Stack& other) :
  container_(other.container_)
{}

template < typename T >
T& nikiforov::Stack< T >::back()
{
  return container_.back();
}

template < typename T >
bool nikiforov::Stack< T >::is_empty() noexcept
{
  return container_.is_empty();
}

template < typename T >
size_t nikiforov::Stack< T >::getSize()
{
  return container_.getSize();
}

template < typename T >
void nikiforov::Stack< T >::push_back(const T& value)
{
  container_.push_back(value);
}

template < typename T >
void nikiforov::Stack< T >::pop_back()
{
  container_.pop_back();
}

#endif
