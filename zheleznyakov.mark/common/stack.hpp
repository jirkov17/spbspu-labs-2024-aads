#ifndef STACK_HPP
#define STACK_HPP
#include <list.hpp>
namespace zheleznyakov
{
  template < typename T >
  class Stack
  {
    public:
      Stack() = default;
      Stack(const Stack< T > & other);
      Stack(Stack< T > && other);
      ~Stack() = default;
      bool empty() const noexcept;
      size_t size() const noexcept;
      T & top() const;
      void push(const T & value);
      void pop();
      void swap(const List< T > & other);
    private:
      List< T > container_;
  };
}

template< typename T >
zheleznyakov::Stack< T >::Stack(const Stack< T > & other):
  container_(other.container_)
{}

template< typename T >
zheleznyakov::Stack< T >::Stack(Stack< T > && other):
  container_(other.container_)
{
  other.container_ = nullptr;
}

template< typename T >
bool zheleznyakov::Stack< T >::empty() const noexcept
{
  return container_.isEmpty();
}

template< typename T >
size_t zheleznyakov::Stack< T >::size() const noexcept
{
  return container_.getSize();
}

template< typename T >
T & zheleznyakov::Stack< T >::top() const
{
  return container_[0];
}

template< typename T >
void zheleznyakov::Stack< T >::push(const T & value)
{
  container_.pushFront(value);
}

template< typename T >
void zheleznyakov::Stack< T >::pop()
{
  container_.popFront();
}

template< typename T >
void zheleznyakov::Stack< T >::swap(const List< T > & other)
{
  container_ = other;
}
#endif
