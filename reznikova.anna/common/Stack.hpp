#ifndef STACK_HPP
#define STACK_HPP
#include <List.hpp>

namespace reznikova
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack & other);
    Stack(Stack && other);
    ~Stack() = default;
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
reznikova::Stack< T >::Stack():
  data_(List< T >())
{}

template< typename T >
reznikova::Stack< T >::Stack(const Stack & other):
  data_(other.data_)
{}

template< typename T >
reznikova::Stack< T >::Stack(Stack && other):
  data_(other.data_)
{
    other.data_.clean();
}

template< typename T >
void reznikova::Stack< T >::push(const T & value)
{
  data_.pushBack(value);
}

template< typename T >
void reznikova::Stack< T >::pop()
{
  data_.popBack();
}

template< typename T >
bool reznikova::Stack< T >::empty() noexcept
{
  return data_.empty();
}

template< typename T >
T & reznikova::Stack< T >::getValue() const noexcept
{
  return data_.getBack();
}

template< typename T >
size_t reznikova::Stack< T >::getSize() const noexcept
{
  return data_.getSize();
}

template< typename T >
void reznikova::Stack< T >::reverse()
{
  return data_.reverse();
}

#endif
