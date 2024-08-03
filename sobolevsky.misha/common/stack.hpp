#ifndef STACK_HPP
#define STACK_HPP

#include <utility>
#include <stdexcept>
#include <memory>
#include <list.hpp>

namespace sobolevsky
{
  template< typename T >
  class Stack
  {
  public:
    Stack();
    Stack(const Stack& rhs) noexcept;
    Stack(Stack&& rhs);
    ~Stack();

    void push(const T& data);
    T top();
    void pop();
    bool empty();
    long long size();
  private:
    List< T > list;
  };
}

template< typename T >
sobolevsky::Stack< T >::Stack()
{
  list = List< T >();
}

template< typename T >
sobolevsky::Stack< T >::Stack(const Stack& rhs) noexcept
{
  list = rhs.list;
}

template< typename T >
sobolevsky::Stack< T >::Stack(Stack&& rhs)
{
  list = std::move(rhs.list);
}

template< typename T >
sobolevsky::Stack< T >::~Stack()
{
  list.clear();
}

template< typename T >
void sobolevsky::Stack< T >::push(const T& data)
{
  list.pushFront(data, "");
}

template< typename T >
T sobolevsky::Stack< T >::top()
{
  if (list[0] == nullptr)
  {
    throw std::logic_error("stack is empty");
  }
  return list[0]->data;
}

template< typename T >
void sobolevsky::Stack< T >::pop()
{
  list.popFront();
}

template< typename T >
bool sobolevsky::Stack< T >::empty()
{
  return (list.empty());
}

template< typename T >
long long sobolevsky::Stack< T >::size()
{
  return list.getSize();
}

#endif
