#ifndef STACK_HPP
#define STACK_HPP
#include "list.hpp"

namespace mihalchenko
{
  template < typename T >
  class Stack
  {
  public:
    Stack() = default;
    Stack(const Stack< T > &copy);
    ~Stack() = default;
    void push(const T &data);
    void pop();
    const T getT();
    T &operator[](const size_t ind);
    void clear();
    size_t getSize();
    void setSize(const size_t size);
    bool isEmpty() noexcept;
    T & getElem() noexcept;

  private:
    List< T > containStack;
  };
}

template < typename T >
mihalchenko::Stack< T >::Stack(const Stack< T > &copy)
{
  containStack(copy);
}

template < typename T >
void mihalchenko::Stack< T >::push(const T &data)
{
  containStack.push_front(data);
}

template < typename T >
void mihalchenko::Stack< T >::pop()
{
  containStack.pop_front();
}

template < typename T >
const T mihalchenko::Stack< T >::getT()
{
  T res = containStack.getT();
  return res;
}

template < typename T >
T &mihalchenko::Stack< T >::operator[](size_t index)
{
  return containStack[index];
}

template < typename T >
void mihalchenko::Stack< T >::clear()
{
  containStack.clear();
}

template < typename T >
size_t mihalchenko::Stack< T >::getSize()
{
  return containStack.getSize();
}

template < typename T >
void mihalchenko::Stack< T >::setSize(const size_t size)
{
  containStack.setSize(size);
}

template < typename T >
bool mihalchenko::Stack< T >::isEmpty() noexcept
{
  return containStack.empty();
}

template < typename T >
T & mihalchenko::Stack< T >::getElem() noexcept
{
  return containStack.front();
}

#endif
