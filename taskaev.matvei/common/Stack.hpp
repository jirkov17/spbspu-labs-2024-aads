#ifndef STACK_HPP
#define STACK_HPP
#include "List.hpp"

namespace taskaev
{
  template < typename T >
  class Stack
  {
  public:
    Stack();
    Stack(Stack< T >&& other);
    Stack(const Stack< T >& other);
    ~Stack() = default;
    void push(const T& value);
    void pop();
    bool isEmpty() const noexcept;
    T& top();
  private:
    List< T > container_;
  };
}

template < typename T >
taskaev::Stack< T >::Stack():
  container_(List< T >())
{}

template< typename T >
taskaev::Stack< T >::Stack(const Stack< T >& other):
  container_(other)
{}

template< typename T >
taskaev::Stack< T >::Stack(Stack< T >&& other):
  container_(other.container_)
{}

template < typename T >
void taskaev::Stack< T >::push(const T& value)
{
  container_.pushFront(value);
}

template < typename T >
void taskaev::Stack< T >::pop()
{
  container_.popFront();
}

template < typename T >
bool taskaev::Stack< T >::isEmpty() const noexcept
{
  return container_.isEmpty();
}

template < typename T >
T& taskaev::Stack< T >::top()
{
  return container_.front();
}

#endif
