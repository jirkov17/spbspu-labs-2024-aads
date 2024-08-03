#ifndef STACK_HPP
#define STACK_HPP
#include <doublelist.hpp>

namespace kovshikov
{
  template< typename T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T >& s);
    Stack(Stack< T >&& s);
    ~Stack() = default;

    void push(const T& val);
    T& top();
    void pop();

    size_t getSize() const;
    bool isEmpty() const noexcept;
  private:
    DoubleList< T > stack;
  };
}

template< typename T >
kovshikov::Stack< T >::Stack(const Stack< T >& s)
{
  stack = s.stack;
}

template< typename T >
kovshikov::Stack< T >::Stack(Stack< T >&& s)
{
  stack = std::move(s.stack);
}

template< typename T >
void kovshikov::Stack< T >::push(const T& val)
{
  stack.pushBack(val);
}

template< typename T >
T& kovshikov::Stack< T >::top()
{
  return stack.back();
}

template< typename T >
void kovshikov::Stack< T >::pop()
{
  stack.popBack();
}

template< typename T >
size_t kovshikov::Stack< T >::getSize() const
{
  size_t size = 0;
  typename DoubleList< T >::Iterator start = stack.begin();
  typename DoubleList< T >::Iterator finish = stack.end();
  while(start != finish)
  {
    size += 1;
    start++;
  }
  return size;
}

template< typename T >
bool kovshikov::Stack< T >::isEmpty() const noexcept
{
  return stack.empty();
}

#endif
