#ifndef STACK_HPP
#define STACK_HPP
#include "List.hpp"

namespace sukacheva {
  template < typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack&);
    Stack(Stack&& other);
    ~Stack() = default;

    bool empty() const noexcept;
    size_t getSize() noexcept;
    void push(const T& value);
    void push(T&& value);
    T& top() const noexcept;
    void pop();
    void swap(Stack& other) noexcept;

  private:
    List< T > container;
  };
}

template< typename T >
sukacheva::Stack< T >::Stack() :
  container(List< T >())
{}

template< typename T >
sukacheva::Stack< T >::Stack(const Stack& cont) :
  container(cont.container)
{}

template< typename T >
sukacheva::Stack< T >::Stack(Stack&& other) :
  container(other.container)
{
  other.container.clean();
}

template< typename T >
bool sukacheva::Stack< T >::empty() const noexcept
{
  return container.empty();
}

template< typename T >
size_t sukacheva::Stack< T >::getSize() noexcept
{
  return container.getSize();
}

template< typename T >
void sukacheva::Stack< T >::push(const T& value)
{
  container.pushFront(value);
}

template< typename T >
void sukacheva::Stack< T >::push(T&& value)
{
  container.pushFront(value);
}

template< typename T >
T& sukacheva::Stack< T >::top() const noexcept
{
  return container.front();
}

template< typename T >
void sukacheva::Stack< T >::pop()
{
  container.popFront();
}

template< typename T >
void sukacheva::Stack< T >::swap(Stack& other) noexcept
{
  container.swap(other.container);
}

#endif
